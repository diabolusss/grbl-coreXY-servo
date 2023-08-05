/*
  cpu_map.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The cpu_map.h files serve as a central pin mapping selection file for different processor
   types, i.e. AVR 328p or AVR Mega 2560. Each processor has its own pin mapping file.
   (i.e. cpu_map_atmega328p.h)  Grbl officially supports the Arduino Uno, but the 
   other supplied pin mappings are supplied by users, so your results may vary. */
/* cpu_map.h 文件作为一个引脚功能分派选择文件的中心，用于不同的处理器类型，例如： AVR 328P或
  AVR Mega 2560. 每个处理器有它自己的引脚功能分派文件，(例如 cpu_map_atmega328p.h). Grbl官方支持
 Arduino Udo， 但其他的引脚功能分派文件由用户提供，因此你可能有不同的文件。  */
// NOTE: With new processors, only add the define name and filename to use.
// 注意：对于新的处理器，仅仅加入需要使用定义名和文件名

#ifndef cpu_map_h
#define cpu_map_h


#ifdef CPU_MAP_ATMEGA328P // Grbl官方支持的Arduion Uno  (Arduino Uno) Officially supported by Grbl.
  #include "cpu_map/cpu_map_atmega328p.h"
#endif

#ifdef CPU_MAP_ATMEGA2560 // @EliteEng 在开发中的 (Arduino Mega 2560) Working @EliteEng
  #include "cpu_map/cpu_map_atmega2560.h"
#endif

/* 
#ifdef CPU_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and edit one of the available cpu
  // map files and modify it to your needs. Make sure the defined name is also changed in
  // the config.h file.
  // 对不同的处理器或者定制的引脚分配图，复制一个上面的CPU分配文件，按你的需求修改它。还有，要
  // 确保在conffig.h文件里也修改了这个被定义的名字。
#endif
*/

#endif
