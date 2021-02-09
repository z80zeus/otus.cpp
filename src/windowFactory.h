#pragma once

#include <memory>

#include <boost/program_options.hpp>

#include "mainWindow.h"

namespace z80 {
  /**
   * @brief Функция создаёт окна разных типов в соответствии с параметрами.
   * @param param Параметры, в соответствии с которыми функция создаёт окна того или иного типа.
   * @return Указатель на объект типа окно.
   */
  std::unique_ptr<z80::mainWindow> createWindow (const boost::program_options::variables_map& param);
};
