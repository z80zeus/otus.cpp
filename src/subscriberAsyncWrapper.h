/**
 * @brief Файл содержит описание шаблонного класса асинхронной обёртки над Подписчиком (subscriber).
 * @author Владимир Лазарев solock@mail.ru
 */
#pragma once

#include "semaphore.h"
#include "subscriber.h"

#include <cstddef>    // std::size_t
#include <functional> // std::bind
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace z80 {
  /**
   * @brief Шаблонный класс-обёртка для обеспечения асинхронной работы подписчика в паре Издатель-Подписчик.
   * @tparam Subscriber Тип класса, реализующего интерфейс Подписчика.
   * @tparam ThreadsNum Количество рабочих потоков, которые следует запустить в обёртке.
   * @tparam DataType Тип с которым работет Subscriber. Нужно для типизации очереди сообщений внутри обёртки.
   * @details Данный класс в паре Издатель-Подписчик является обычным синхронным Подписчиком, для чего он наследуется
   * он класса z80::subscriber<> Но внутри себя реализует поддержку
   * асихнронной работы с сообщениями.
   * Для этого он содержит внутри себя очередь сообщений, куда помещает пришедшие сообщения и освобождает Издателя от
   * ожидания их обработки. Т.е. для издателя вызов такого Подписчика становится неблокирующим.
   * Сообщения из очереди выбираются отдельными, рабочими потоками, которые объект данного класса создаёт в конструкторе.
   * Количество потоков указано в параметре шаблона TreadsNum.
   * Каждый поток в качестве локального объекта создаёт экземпляр класса Subscriber и передаёт сообщение из очереди - ему.
   * Каждое сообщение обрабатывается один раз одним из рабочих потоков. Это обеспечивается вызовом метода notify_one()
   * внутренней conditional variable - переменной, предназначенной для синхронизации работы с очередью сообщений.
   * В деструкторе объекта устанавливается флаг завершения работы и вызывается метод notify_all(), что приводит к
   * завершению работы всех рабочих потоков.
   */
  template<typename Subscriber, std::size_t ThreadsNum = 2, typename DataType = typename Subscriber::MessageType>
  class subscriberAsyncWrapper: public z80::subscriber<DataType> {
    public:
    explicit subscriberAsyncWrapper() {
      threads.reserve(ThreadsNum);
      for (auto i = 0; i < ThreadsNum; ++i)
        threads.emplace_back(std::bind(&subscriberAsyncWrapper::workThread, this));
    }

    ~subscriberAsyncWrapper() override {
      finishFlag = true;
      queueNotifier.post(ThreadsNum);
      for (auto& t : threads)
        t.join();
    }

    void update(const DataType& commandBlock) override {
      std::unique_lock<std::mutex> locker(queueMutex);
      inputQueue.push(commandBlock);
      locker.unlock(); // Упредительное снятие блокировки с мьютекса, чтобы workThread проснувшись не заснул сразу же на нём.
      queueNotifier.post();
    }

    private:
    void workThread () {
      Subscriber subscriberImpl;
      DataType readBuffer;
      while (true) {
        queueNotifier.wait();
        std::unique_lock<std::mutex> locker(queueMutex);
        if (inputQueue.empty()) {
          if (finishFlag) break;
          else continue;
        }

        readBuffer = move(inputQueue.front());
        inputQueue.pop();
        locker.unlock();
        subscriberImpl.update(readBuffer);
      }
    }

    /**
     *
     */
    bool                     finishFlag = false;
    std::queue<DataType>     inputQueue;
    std::mutex               queueMutex;
    z80::semaphore           queueNotifier;
    std::vector<std::thread> threads;
  };
}
