#pragma once

#include <cstddef>      // std::size_t
#include <unordered_map>

namespace z80 {
  /**
   * @brief Класс, реализующий бесконечную (infinite) разреженную (dispersed) матрицу (matrix): idMatrix
   * @tparam T тип хранимого в контейнере значения.
   * @tparam DefaultValue значение по-умолчанию для неинициализированных ячеек.
   * @tparam Dim Количество измерений матрицы (1 - вектор, 2 - прямоугольная, 3 - кубическая и т.д.)
   */
  template <typename T, T DefaultValue = 0, std::size_t Dim = 2>
  class idMatrix {

    using Matrix = z80::idMatrix<T,DefaultValue>;

//    /**
//     * @brief Ячейка таблицы
//     */
//    class cell {
//      public:
//      /**
//       *
//       * @param value
//       * @param index
//       */
//      explicit cell(Matrix::row& r, std::size_t index): idx(index), row_{r};
//      /**
//       *
//       * @param value
//       * @return
//       */
//      cell& operator=(const T& value) {
//        row_.set(idx, value);
//        return *this;
//      };
//      /**
//       *
//       * @return
//       */
//      explicit operator T() const {
//        return row_.get(idx);
//      };
//
//      private:
//      std::size_t idx;
//      Matrix::row& row_;
//    };
//
//    /**
//     * @brief Класс, описывающий разреженную строку таблицы.
//     */
//    class row {
//      public:
//      /**
//       * @brief Строка должна знать в какой матрице она находится. Конструирование строки без параметров запрещено.
//       */
//      row() = delete;
//
//      /**
//       * @brief Создание новой строки.
//       * @param matrix Ссылка на объект матрицы к которому относится данная строка. Это нужно для изменения её свойства dataSize;
//       */
//      explicit row(Matrix& matrix): matrix_(matrix) {};
//
//      /**
//       * @brief Константный оператор обращения по индексу возвращает константную ссылку на значение.
//       * @param index Индекс требуемого значения в строке.
//       * @return Константная ссылка на значение. Если значения по данному индексу нет - вернёт ссылку на значение по-умолчанию.
//       */
//      const Matrix::row&
//      operator[](std::size_t index) const {
//        if (cells.contains(index)) return cells.at(index);
//        return defaultValue;
//      };
//
//      /**
//       * @brief Оператор обращения по индексу возвращает ссылку на значение.
//       * @param index Индекс требуемого значения в строке.
//       * @return Ссылка на значение.
//       */
//      T& operator[](std::size_t index) {
//        if (!cells.contains(index)) {
//          cells.emplace(std::make_pair(index, T{V}));
//          matrix_.elemNum++;
//        }
//        return cells.at(index);
//      };
//
//      /**
//       * Копирование строк на данном этапе разработки - запрещено.
//       */
//      Matrix::row& operator=(const Matrix::row&) = delete;
//      Matrix::row& operator=(Matrix::row&)       = delete;
//
//      private:
//      /**
//       * @brief Инициализированные значения (не по-умчолчанию) содержащиеся в строке.
//       */
//      std::unordered_map<std::size_t, Matrix::cell> cells;
//
//      /**
//       * @brief Ссылка на матрицу, где находится данная строка. Инициализируется конструктором.
//       */
//      Matrix& matrix_;
//
//      /**
//       * @brief Значение по-умолчанию, которое возвращается по доступу к неинициализированному элементу строки.
//       */
//      const Matrix::row defaultValue {V};
//    };
//
//    /**
//     * @brief Строка изменяет количество элементов в контейнере (elemNum).
//     */
//    friend Matrix::row;
//
//    public:
//    /**
//     * @brief По-умолчанию создаётся пустая матрица.
//     */
//    idMatrix() = default;
//
//    /**
//     * @brief Оператор константного доступа к элементу контейнера.
//     * @param index Индекс строки к которой обращается вызывающий код.
//     * @return Константная ссылка на строку с индексом index. Если строка с данным индексом пустая - возвращается
//     * ссылка на строку-заглушку, которая на обращение по любому индксу внутри строки возвращает одно и то же значение по-умолчанию - V.
//     */
//    const Matrix::row&
//    operator[] (std::size_t index) const {
//      if (!rows.contains(index)) return defaultRow;
//      return rows.at(index);
//    };
//
//    /**
//    * @brief Оператор доступа к элементу контейнера.
//    * @param index Индекс строки к которой обращается вызывающий код.
//    * @return Cсылка на строку с индексом index.
//    */
//    Matrix::row&
//    operator[] (std::size_t index) {
//      if (!rows.contains(index))
//        rows.emplace(std::make_pair(index, z80::idMatrix<T,V>::row{*this}));
//      return rows.at(index);
//    };
//
//    /**
//     * @brief Функция возвращает количество элементов, содержащихся в контейнере.
//     * @return Количество элементов в контейнере.
//     */
//    [[maybe_unused]] std::size_t
//    size () {
//
//      return elemNum;
//    }
//
//    private:
//    /**
//     * @brief Хэш-таблица строк матрицы. Ключ = индекс строки, значение = строка.
//     */
//    std::unordered_map<std::size_t, Matrix::row>  rows;
//
//    /**
//     * @brief Количество инициализированных элементов в матрице. Увеличивается объектами класса row при добавлении нового элемента,
//     * для чего этот клас объявлен дружественным (friend).
//     */
//    std::size_t                                   elemNum = std::size_t{0};
//
//    /**
//     * @brief Строка по-умолчанию, которая возвращается при доступе к неинициализированной строке.
//     * @details Этат объект возвращается только при доступе по константному operator[].
//     * Поэтому эта строка всегда останется пустой и при доступе по любому индексу внутри строки - будет возвращать
//     * значение по-умчоланию V.
//     */
//    const Matrix::row                             defaultRow {*this};

      template<std::size_t Num>
      class indexer {
        public:
        indexer<Num-1>& operator[] (std::size_t index) {
          return indexer<Num-1>{};
        };
      };

      template<>
      class indexer<0> {
        public:
        T& operator[] (std::size_t index) { return T{0}; }
      };

      indexer<Dim>& operator[] (std::size_t index) {
        return indexer<Dim>{};
      }
  };
}