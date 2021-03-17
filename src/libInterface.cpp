#include "libInterface.h"

#include "commandBlockFiler.h"
#include "commandBlockPrinter.h"
#include "commandStateMachine.h"
#include "publisherCommandsFromStream.h"
#include "subscriberAsyncWrapper.h"

#include <atomic>     // std::atomic
#include <map>
#include <mutex>      // std::mutex, std::lock_guard
#include <new>        // std::bad_alloc
#include <stdexcept>  // std::out_of_range
#include <sstream>    // std::istringstream

using namespace async;
using namespace std;
using namespace z80;

/**
 * @brief Словарь конечных автоматов, обрабатывающих команды.
 * @details Ключом является текущее значение счётчика автоматов nextMachineIndex. Этот ключ возвращается в качестве
 * async::handle_t функцией async::connect
 */
map<size_t, commandStateMachine>  commandMachines;

/**
 * @brief Индекс, с которым следующий автомат будет добавлен в контейнер автоматов commandMachines.
 */
atomic<size_t> nextMachineIndex = 0;

/**
 * @brief Мьютекс для организации безопасного многопоточного доступа к словарю автоматав.
 */
mutex commandMachinesMutex;

/**
 * @brief Объект, выводящий блоки команд в стандартный вывод.
 * @details Работает в одном (шаблонный параметр 1) отдельном потоке.
 */
subscriberAsyncWrapper<commandBlockPrinter, 1> printer;

/**
 * @brief Объект, записывающий блоки команд в файлы.
 * @details Работает двумя (шаблонный параметр 2) отдельными потоками, которые берут блоки команд в работу в
 * произвольном порядке.
 */
subscriberAsyncWrapper<commandBlockFiler, 2> filer;

handle_t
async::connect (size_t bulk) {
  lock_guard<mutex> locker(commandMachinesMutex);
  if (commandMachines.find(nextMachineIndex) != commandMachines.end())  // Все ключи заняты
    throw bad_alloc();
  commandStateMachine csm;
  csm.setStaticBlockSize(bulk);
  csm.subscribe(printer);
  csm.subscribe(filer);
  commandMachines.emplace(nextMachineIndex, move(csm));
  return reinterpret_cast<handle_t>(nextMachineIndex++);
}

void
async::receive (handle_t handle, const char* data, size_t size) {
  auto machineIndex = reinterpret_cast<size_t>(handle);
  lock_guard<mutex> locker(commandMachinesMutex);
  if (commandMachines.find(machineIndex) == commandMachines.end())
    throw out_of_range("Wrong handle");

  istringstream is(string(data, size));
  publisherCommandsFromStream commandPublisher(is);
  commandPublisher.subscribe(commandMachines[machineIndex]);
  commandPublisher.start();
}

void
async::disconnect (handle_t handle) {
  auto machineIndex = reinterpret_cast<size_t>(handle);
  lock_guard<mutex> locker(commandMachinesMutex);
  if (commandMachines.find(machineIndex) == commandMachines.end())
    throw out_of_range("Wrong handle");

  commandMachines[machineIndex].stop();
  commandMachines.erase(machineIndex);
}
