#pragma once

class svg;

namespace z80 {
  /**
   * @brief Интерфейс источников данных
   */
  class svgDataSource {
  public:
    /**
     * @brief Прочитать SVG-документ.
     * @return Указатель на xml-документ.
     */
    virtual svg* readSVG() = 0;

    /**
     * @brief Сохранить SVG-документ.
     * @param doc
     * @return
     */
    virtual bool writeSVG(const svg& doc) = 0;

    virtual ~svgDataSource() = 0;
  };
}
