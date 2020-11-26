/**
 * @file Файл содержит учебный аллокатор в соответствии с заданием.
 * @author Владимир Лазарев solock@mail.ru
 * @details Реализовать свой аллокатор памяти, который позволит выполнять операцию резервирования памяти.
 * Далее использовать этот аллокатор с контейнером std::map.
 * Аллокатор должен параметризоваться количеством выделяемых за раз элементов. Освобождение конкретного
 * элемента не предполагается - аллокатор должен освобождать всю память самостоятельно.
 * Аллокатор работает с фиксированным количеством элементов. Попытку выделить большее число элементов считать ошибкой.
 * Опционально реализовать расширяемость аллокатора. При попытке выделить число элементов, которое превышает текущее
 * зарезервированное количество, аллокатор расширяет зарезервированную память.
 * Опционально реализовать поэлементное освобождение.
 * Цель такого аллокатора – снизить количество операций выделения памяти.
*/
#pragma once

#include <cstdlib> // std::malloc, std::free
#include <cstddef> // std::size_t
#include <utility> // std::forward
#include <cmath>   // std::ceil

#include <vector>

#include <iostream>

//#define DEBUG std::cout << "[" << this << "]: " << __PRETTY_FUNCTION__ << std::endl;
#define DEBUG

namespace z80 {
  /**
   * @brief Аллокатор, резервирующий сразу N элементов и выделяющий их по запросу.
   * @param T - тип элемента, с которым работает аллокатор.
   * @param N - количество элементов, резервируемых при создании аллокатора.
   */
  template <typename T, std::size_t N = 10, bool Extendable = true>
  struct allocator {

    using value_type = T;

    template<typename U>
    struct rebind { typedef z80::allocator<U, N, Extendable> other; };

    /**
     * @brief Конструктор по-умолчанию вызывает функцию инициализации с параметрами по-умолчанию.
     */
    allocator() noexcept(false) {
      DEBUG
      init ();
    };

    /**
     * @brief Копирующий конструктор ничего не копирует, а инициализирует объект, вызывая соответствующую функцию.
     */
    allocator(const z80::allocator<T, N, Extendable>&) {
      DEBUG
      init (N, Extendable);
    }

//    allocator(z80::allocator<T, N, Extendable>&&) {
//      DEBUG
//      init (N, Extendable);
//    }

     /**
     * @brief Деструктор освобождает выделенную память и приводит объект в исходное состояние.
     */
    ~allocator() noexcept {
      DEBUG

      while(chunksPages) {
        if (chunksPages->head) std::free (chunksPages->head);
        auto page = chunksPages;
        chunksPages = chunksPages->next;
        std::free(page);
      }
      chunksPages = nullptr;
    };

    /**
     * @brief Выделить непрерывную область памяти для n элементов.
     * @param n Количество элементов для которых нужно выделить непрерывную область памяти.
     * @return Указатель на первый элемент.
     * @throw В случае невозможности выделения памяти - выбрасывает исключение std::bad_alloc.
     * @details Ищет в списке блоков - физически непрерывную область (блоки, лежащие в памяти один за другим)
     * и возвращает указатель на первый элемент, с которого эта непрерывная область начинается.
     * Если такой непрерывной области не найдено, то дальнейшее поведение заивисит от параметра расширяемости аллосатора.
     * Если аллокатор не раширяемый - выбрасывается исключение std::bad_alloc.
     * В противном случае - создаётся новый буффер, прикрепляющийся к существующему.
     */
    T* allocate (std::size_t n) noexcept(false) {
      DEBUG

      if (n == 0) throw std::bad_alloc ();

      auto chunks = getContinuousN(chunksHead, n);
      if (chunks.first == nullptr) {
        if (!Extendable) throw std::bad_alloc();
        else {
          auto n_ = std::ceil(static_cast<float>(n) / N) * N;
          auto page = createChunkPage(n_);       // Создать новую страницу.
          page->next = chunksPages;              // Поместить новую страницу...
          chunksPages = page;                    // ... в начало списка страниц.

          chunks.first = page->head;             // Непрерывный массив блоков, который "нашёлся" - находится в новой странице.
          chunks.last = page->head + n;          // Т.к. он непрерывный - посчитать последний элемент легко.

          if (chunks.prev == nullptr)            // Новая страница - это единственные свободные блоки в наличии...
            chunksHead = page->head;             // ... сделать их началом списка свободных блоков.
          else                                   // Иначе:
            chunks.prev->next = page->head;      // Прикрепить новый массив блоков к хвосту предыдущего.
        };
      }

      if (chunks.first == chunksHead)            // Найденный массив - в начале списка...
        chunksHead = chunks.last->next;          // ...переместить голову.
      else                                       // Иначе:
        chunks.prev->next = chunks.last->next;   // "Вырезать" этот массив из списка.

      return reinterpret_cast<T*>(chunks.first);
    };

    /**
     * @brief Освободить область выделенную для n элементов.
     * @param p Указатель на начало области памяти.
     * @param n Количество элементов, находящихся в этой области.
     * @details Инициализирует в области памяти связный список блоков и помещает его в начало списка свободных блоков.
     */
    void deallocate (T* p, std::size_t n) noexcept(false) {
      DEBUG

      assert(n > 0);

      auto chunk = reinterpret_cast<chunkT*>(p);
      initChunks (chunk, n);
      (chunk + n - 1) -> next = chunksHead; // Т.к. область непрерывная - можно воспользоваться арифметикой указателей.
      chunksHead = chunk;                   // Освободившуюся область - в начало списка блоков.
    };

    /**
       * @brief Функция вызывается allocator_traits при копировании контейнера.
       * @return Новый экземпляр аллокатора, со своим внутренним массивом данных.
       */
//    z80::allocator<T, N, Extendable>
//    select_on_container_copy_construction() const {
//        DEBUG
//        return z80::allocator<T, N, Extendable>();
//      }

    private:
      void
      init(std::size_t n = N, bool ext = Extendable) {
        static_assert(sizeof(T) >= sizeof(chunkT*), "z80::allocator doesn't support type less than size of pointer.");
        pageSize = n;
        extendable = ext;
        chunksPages = createChunkPage(N);
        chunksHead = chunksPages->head;
      }


      /**
     * @brief Объединение (union) для проддержки однонаправленного списка блоков данных.
     * @union
     */
    union chunkT {
      T       data; /** Полезная нагрузка (данные). Сама по себе аллокатору не нужна. Используется только для определения размера chunkT */
      chunkT* next; /** Указатель на следующий элемент списка */
    };

    chunkT* chunksHead  = nullptr; /** Указатель на голову списка блоков. Будет изменяться при выделении/освобождении памяти. */
    std::size_t sizeOfData = sizeof(T);
    bool extendable = Extendable;

    /**
     * @brief Структура, описывающая 1 страницу блоков. Блоки выделяются страницами.
     * @struct
     */
    struct chunksPage {
      chunkT* head = nullptr;     /** Указатель на головной блок этой страницы. Инициализируется при выделении блока, удаляется - при освобождении. */
      chunksPage* next = nullptr; /** Указатель на следующую страницу. Страницы образуют однонаправленный список. */
    };

    std::size_t pageSize = N;

    /**
     * @brief Страницы блоков которыми оперирует аллокатор.
     * Список инициализируется конструктором.
     * Расширяется - при расширении памяти.
     * Удаляется - деструктором.
     */
    chunksPage* chunksPages = nullptr;

    /**
     *
     * @param n
     * @return
     */
    auto
    createChunkPage(std::size_t n) {
      auto page = reinterpret_cast<chunksPage*>(std::malloc(sizeof(chunksPage)));
      if (page == nullptr) throw std::bad_alloc();
      page->next = nullptr;

      page->head = reinterpret_cast<chunkT*>(std::malloc(sizeof(chunkT) * n));
      if (page->head == nullptr) {
        std::free(page);
        throw std::bad_alloc();
      }
      initChunks(page->head, n);
      return page;
    }


      /**
     * @brief Инициализировать НЕПРЕРЫВНУЮ область памяти в качестве списка блоков.
     * @param head Голова списка.
     * @param num Количество элементов в списке.
     * @details Инициализирует область памяти, превращая её в связный однонаправленный список блоков.
     */
    void
    initChunks (chunkT* head, size_t num) noexcept {
      while (--num != 0) {
        head->next = head + 1;
        ++head;
      };
      head->next = nullptr;
    };

    /**
     * @brief Структура, описывающая непрерывный массив блоков.
     */
    struct chunkArray {
      chunkT* prev  = nullptr; /** Указатель на блок, находящийся в списке ПЕРЕД первым блоком массива. */
      chunkT* first = nullptr; /** Указатель на первый блок в массиве. */
      chunkT* last  = nullptr; /** Указатель на последний блок в массиве */
    };

    /**
     * @brief Возвращает непрерывный массив блоков (физически следующих один за другим) в списке свободных блоков аллокатора.
     * @param head Голова массива. Поиск начинается с этого блока.
     * @param n Требуемая длина массива (в блоках)
     * @return Структура chunkArray описывающая непрерывный массив блоков в списке свободных блоков аллокатора.
     * @details Функция перебирает список блоков начиная с head в поисках непрерывного (в памяти) свободного массива
     * размером n. При обнаружении сбоя непрерывности - начинает новый поиск со сбойного, блока.
     */
    auto getContinuousN (chunkT *head, std::size_t n) {
      chunkT *first = head, *prev = nullptr;
      for (decltype(n) i = 1;
           head != nullptr;
           head = head->next, ++i)
      {
        if (i >= n) return chunkArray { prev, first, head }; // Необходимое количество блоков найдено.
        if (head->next == head + 1) continue;                // Следующий блок в памяти - свободен. Перейти к нему.
        // Сбой последовательности свободных блоков - начать заново.
        i = 0;
        prev = head;
        first = head->next;
      }
      return chunkArray { prev, nullptr, nullptr };
    }
  };

  /**
   * @brief Оператор неравенства аллокаторов z80::allocator. Эти аллокаторы всегда не равны.
   * @tparam T Тип шаблона левого аллокатора.
   * @tparam U Тип шаблона правого аллокатора.
   * @return true.
   */
  template<typename T, typename U>
  bool operator!=(const z80::allocator<T, 0, true>&, const z80::allocator<U, 0, true>&) { return true; }

  /**
   * @brief Оператор равенства аллокаторов z80::allocator. Эти аллокаторы всегда не равны.
   * @tparam T Тип шаблона левого аллокатора.
   * @tparam U Тип шаблона правого аллокатора.
   * @return false.
   */
  template<typename T, typename U>
  bool operator==(const z80::allocator<T, 0, true>&, const z80::allocator<U, 0, true>&) { return false; }
}

