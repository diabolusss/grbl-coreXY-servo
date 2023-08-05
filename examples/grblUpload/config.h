/*
  config.h - compile time configuration
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon
  Copyright (c) 2009-2011 Simen Svale Skogsrud

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

// This file contains compile-time configurations for Grbl's internal system. For the most part,
// users will not need to directly modify these, but they are here for specific needs, i.e.
// performance tuning or adjusting to non-typical machines.
// 文件包含了grbl的内部系统的编译配置.对绝大部分设定,用户不需要在这里直接修改,但列在这里是有特别的用途:例如,
// 调节性能,或为某台特定的机器调整


// IMPORTANT: Any changes here requires a full re-compiling of the source code to propagate them.
// 重要:这里有任何改变后都需要从新编译所有源代码

#ifndef config_h
#define config_h
#include "grbl.h" // 为了Arduino的兼容性 For Arduino IDE compatibility.


// Default settings. Used when resetting EEPROM. Change to desired name in defaults.h
//默认设置, 当重设EEPROM时使用,在default.h里可以改成其他的名字

#define DEFAULTS_GENERIC

// Serial baud rate
// 设置波特率
#define BAUD_RATE 115200

// Default cpu mappings. Grbl officially supports the Arduino Uno only. Other processor types
// may exist from user-supplied templates or directly user-defined in cpu_map.h
// 默认的CPU映射, grbl仅正式支持Arduino Uno.其他的处理器类型需要使用用户提供的模板,或直接在cpu_map.h中定义
#define CPU_MAP_ATMEGA328P // Arduino Uno CPU


// Define realtime command special characters. These characters are 'picked-off' directly from the
// serial read data stream and are not passed to the grbl line execution parser. Select characters
// that do not and must not exist in the streamed g-code program. ASCII control characters may be
// used, if they are available per user setup. Also, extended ASCII codes (>127), which are never in
// g-code programs, maybe selected for interface programs.
// NOTE: If changed, manually update help message in report.c.
// 定义实时命令特殊字符. 这些字符被直接从串口接收数据流中'取出',没有传递给grbl命令行处理分析器. 选择那些一定不会
// 在g代码中出现的字符. 根据用户的设定,可能使用ASCII控制字符.扩展的ASCII代码(>127),因为不会在g代码中出现,
// 可以被选作接口程序
// 注意:如果被改变了,要手工更新report.c的帮助信息
#define CMD_STATUS_REPORT '?'
#define CMD_FEED_HOLD '!'
#define CMD_CYCLE_START '~'
#define CMD_RESET 0x18 // ctrl-x.
#define CMD_SAFETY_DOOR '@'

// If homing is enabled, homing init lock sets Grbl into an alarm state upon power up. This forces
// the user to perform the homing cycle (or override the locks) before doing anything else. This is
// mainly a safety feature to remind the user to home, since position is unknown to Grbl.
// 如果使能了返航, 返航初始化锁 会在上电时 把grbl设为警报状态. 这回强制用户在执行任何其他动作前,执行返航循环(或改变这个锁).
// 主要是为了安全提示用户返航, 因为这时grbl还不知道起始位置
#define HOMING_INIT_LOCK // Comment to disable

// Define the homing cycle patterns with bitmasks. The homing cycle first performs a search mode
// to quickly engage the limit switches, followed by a slower locate mode, and finished by a short
// pull-off motion to disengage the limit switches. The following HOMING_CYCLE_x defines are executed
// in order starting with suffix 0 and completes the homing routine for the specified-axes only. If
// an axis is omitted from the defines, it will not home, nor will the system update its position.
// Meaning that this allows for users with non-standard cartesian machines, such as a lathe (x then z,
// with no y), to configure the homing cycle behavior to their needs.
// 利用位掩码,定义返航循环的形式. 返航循环,首先执行一个搜索模式,很快的触碰到限位器开关,然后是一个较慢的定位模式,
// 最后用一个简短的下拉运动,脱离限位器开关. 后面的HOMING_CYCLE_x定义的执行次序是从后缀0开始,仅在特定轴的返航处理中结束.
// 如果某个轴在定义里被省略了, 它将没有返航,系统也不会更新它的位置.
// 这意味着,允许用户可以使用非标准的笛卡尔机器,比如车床(x轴,然后Z轴,没有y轴), 根据需要配置返航循环的行为.

// NOTE: The homing cycle is designed to allow sharing of limit pins, if the axes are not in the same
// cycle, but this requires some pin settings changes in cpu_map.h file. For example, the default homing
// cycle can share the Z limit pin with either X or Y limit pins, since they are on different cycles.
// By sharing a pin, this frees up a precious IO pin for other purposes. In theory, all axes limit pins
// may be reduced to one pin, if all axes are homed with seperate cycles, or vice versa, all three axes
// on separate pin, but homed in one cycle. Also, it should be noted that the function of hard limits
// will not be affected by pin sharing.
// NOTE: Defaults are set for a traditional 3-axis CNC machine. Z-axis first to clear, followed by X & Y.
// 注意: 如果几个轴没有在一个循环里,返航循环的设计允许它们共享限位器引脚, 但需要在cpu_map.h里修改一些引脚的设置值.
// 例如, 默认的返航循环里,Z轴可以和X轴或Y轴共享限位引脚, 因为它们在不同的循环里. 共享引脚后,这个引脚可以用于别的用途.
// 理论上,如果所有的轴在不同的循环返航, 那么所有的轴限位器可以共用一个引脚, 或者反之,每个轴使用自己的引脚,但在同一个循环里
// 进行返航. 另外,请注意, 引脚共享不会影响硬件限位器的功能
#define HOMING_CYCLE_0 (1<<Z_AXIS)                // 需求:首先移动Z清除工作空间 REQUIRED: First move Z to clear workspace.
#define HOMING_CYCLE_1 ((1<<X_AXIS)|(1<<Y_AXIS))  // 可选: 然后同时移动X,Y OPTIONAL: Then move X,Y at the same time.
// #define HOMING_CYCLE_2                         // 可选: 去掉注释,增加轴掩码,并使能它 OPTIONAL: Uncomment and add axes mask to enable

// Number of homing cycles performed after when the machine initially jogs to limit switches.
// This help in preventing overshoot and should improve repeatability. This value should be one or
// greater.
// 当机器刚开始移向限位器开关时,接着要执行的返航循环的数量
// 这可以防止过冲，并提高重复性。这个值应为1或更高
#define N_HOMING_LOCATE_CYCLE 1 // Integer (1-128)

// After homing, Grbl will set by default the entire machine space into negative space, as is typical
// for professional CNC machines, regardless of where the limit switches are located. Uncomment this
// define to force Grbl to always set the machine origin at the homed location despite switch orientation.
// #define HOMING_FORCE_SET_ORIGIN // 取消注释,使能 Uncomment to enable.

// 返航后, 和其他的专业CNC机器一样, 无论限位开关在哪里被定位, grbl默认会把整个机器空间设置成负数空间,
// 如果想强制grbl总是把机器原点设置在返航的位置,而不管开关的方向,可以取消这个注释

// Number of blocks Grbl executes upon startup. These blocks are stored in EEPROM, where the size
// and addresses are defined in settings.h. With the current settings, up to 2 startup blocks may
// be stored and executed in order. These startup blocks would typically be used to set the g-code
// parser state depending on user preferences.
// 在启动时,grbl执行的程序段的数量. 这些程序段保存在EEPROM里, 大小和地址保存在settings.h 里. 按当前的设定值,
// 最多保存2个启动程序段,并顺序执行它们. 一般根据用户的偏好,用这些启动程序段来设置g代码分析器的状态
#define N_STARTUP_LINE 2 // Integer (1-2)

// Number of floating decimal points printed by Grbl for certain value types. These settings are
// determined by realistic and commonly observed values in CNC machines. For example, position
// values cannot be less than 0.001mm or 0.0001in, because machines can not be physically more
// precise this. So, there is likely no need to change these, but you can if you need to here.
// NOTE: Must be an integer value from 0 to ~4. More than 4 may exhibit round-off errors.
// grbl打印浮点数的小数的数量. 这些设定是根据实际情况和在CNC机器里通常观察到的数值确定的.例如,
// 位置值不能比0.001毫米或0.0001英寸小, 因为物理上,机器不能比这还精确. 因此, 没必要改变这些设定, 但如果需要,
// 你可以在这里做修改.
// 注意: 必须是从0到4的整数, 比4多的整数会导致取整错误
#define N_DECIMAL_COORDVALUE_INCH 4 // 坐标或位置值, 英寸 Coordinate or position value in inches
#define N_DECIMAL_COORDVALUE_MM   3 // 坐标或位置值, 毫米 Coordinate or position value in mm
#define N_DECIMAL_RATEVALUE_INCH  1 // 速度值 英寸/分钟 Rate or velocity value in in/min
#define N_DECIMAL_RATEVALUE_MM    0 // 速度值 毫米/分钟 Rate or velocity value in mm/min
#define N_DECIMAL_SETTINGVALUE    3 // 浮点的小数点 Decimals for floating point setting values

// If your machine has two limits switches wired in parallel to one axis, you will need to enable
// this feature. Since the two switches are sharing a single pin, there is no way for Grbl to tell
// which one is enabled. This option only effects homing, where if a limit is engaged, Grbl will
// alarm out and force the user to manually disengage the limit switch. Otherwise, if you have one
// limit switch for each axis, don't enable this option. By keeping it disabled, you can perform a
// homing cycle while on the limit switch and not have to move the machine off of it.
// #define LIMITS_TWO_SWITCHES_ON_AXES
// 如果你的机器有2个平行的限位开关,你需要使能这个特征. 因为2个开关共享一个引脚, grbl没办法分辨哪一个开关被触发了.
// 这个选项只影响返航, 当一个限位器被使用了, grbl会警报,并强制用户手动解开这个限位开关. 否则, 如果每个轴有一个
// 限位开关, 不要使能这个选项.


// Allows GRBL to track and report gcode line numbers.  Enabling this means that the planning buffer
// goes from 18 or 16 to make room for the additional line number data in the plan_block_t struct
// #define USE_LINE_NUMBERS // Disabled by default. Uncomment to enable.
// 允许grbl追踪和报告g代码的语句编号，使能它意味着规划缓冲从18或16开始，为在plan_block_t结构里的数据提供额外的语句编码编号。

// Allows GRBL to report the real-time feed rate.  Enabling this means that GRBL will be reporting more
// data with each status update.
// NOTE: This is experimental and doesn't quite work 100%. Maybe fixed or refactored later.
// 允许grbl报告实时进给速度. 使能它意味着,在每次状态更新时,grbl会报告更多的数据
// 注意: 这是实验性质的, 不是100%能工作, 以后会改善


// #define REPORT_REALTIME_RATE // 默认禁止, 取消注释使能 Disabled by default. Uncomment to enable.



// Upon a successful probe cycle, this option provides immediately feedback of the probe coordinates
// through an automatically generated message. If disabled, users can still access the last probe
// coordinates through Grbl '$#' print parameters.
// 在一次成功的探测循环后, 这个选项通过一个自动生成的消息发送一个探针坐标的立即反馈. 如果被禁止, 用户可以
// 使用GRLB '$#'打印变量命令访问最新的探针坐标

#define MESSAGE_PROBE_COORDINATES // 默认禁止, 取消注释使能 Enabled by default. Comment to disable.

// Enables a second coolant control pin via the mist coolant g-code command M7 on the Arduino Uno
// analog pin 5. Only use this option if you require a second coolant control pin.
// NOTE: The M8 flood coolant control pin on analog pin 4 will still be functional regardless.
// 在Arduion Uno的第5个引脚,通过g代码命令M7, 使能第二个冷却器的控制引脚. 仅在你需要第二个冷却器是使用这个选项
// 注意: 在第4个引脚使用M8的冷却控制引脚继续有功能

// #define ENABLE_M7 // 默认禁止, 取消注释使能 Disabled by default. Uncomment to enable.

// This option causes the feed hold input to act as a safety door switch. A safety door, when triggered,
// immediately forces a feed hold and then safely de-energizes the machine. Resuming is blocked until
// the safety door is re-engaged. When it is, Grbl will re-energize the machine and then resume on the
// previous tool path, as if nothing happened.
// 这个选项把进给暂停的输入当作一个安全门开关对待. 当安全门被触发时,会立即强制进给暂停, 然后安全的把机器去电. 直到
// 安全门被重新关上才恢复. 这时, Grbl会重新给机器上电, 并恢复先前的刀具路径,好像什么事也没有发生.


// #define ENABLE_SAFETY_DOOR_INPUT_PIN // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// After the safety door switch has been toggled and restored, this setting sets the power-up delay
// between restoring the spindle and coolant and resuming the cycle.
//  在安全门开关被翻转和恢复后, 这个选项在恢复主轴和冷却器, 然后恢复循环, 之间, 设置了一个上电延迟
// NOTE: 延迟毫秒数, 从零到65535 Delay value is defined in milliseconds from zero to 65,535.
#define SAFETY_DOOR_SPINDLE_DELAY 4000
#define SAFETY_DOOR_COOLANT_DELAY 1000

// Enable CoreXY kinematics. Use ONLY with CoreXY machines.
// IMPORTANT: If homing is enabled, you must reconfigure the homing cycle #defines above to
// #define HOMING_CYCLE_0 (1<<X_AXIS) and #define HOMING_CYCLE_1 (1<<Y_AXIS)
// NOTE: This configuration option alters the motion of the X and Y axes to principle of operation
// defined at (http://corexy.com/theory.html). Motors are assumed to positioned and wired exactly as
// described, if not, motions may move in strange directions. Grbl assumes the CoreXY A and B motors
// have the same steps per mm internally.

// 使能 CoreXY运动学， 仅用于 CoreXY机器
// 重要： 如果使能了返航，你必须重新配置上面的返航循环 #defines
// #define HOMING_CYCLE_0 (1<<X_AXIS) and #define HOMING_CYCLE_1 (1<<Y_AXIS)
// 注意： 这个配置选项改变了X和Y轴的运动，它们和在(http://corexy.com/theory.html)定义的操作不同了。
// 电机被假设安装完全和描叙的一样，如果不是这样，运动的方向会很奇怪。grbl假设CcoreXY的A和B电机
// 有相同的 步数/毫米。
// 使能CoreXY运动学. 只用于CoreXY机器
// 重要: 如果使能了返航, 你必须吧新配置返航循环的#define 重新定义成
// #define HOMING_CYCLE_0 (1<<X_AXIS) 和 #define HOMING_CYCLE_1 (1<<Y_AXIS)

// #define COREXY // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// Inverts pin logic of the control command pins. This essentially means when this option is enabled
// you can use normally-closed switches, rather than the default normally-open switches.
// NOTE: Will eventually be added to Grbl settings in v1.0.
// 翻转控制命令引脚的引脚逻辑. 如果使能这个选项,你可以使用常闭开关,而不是默认的常开开关.

// #define INVERT_CONTROL_PIN // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// Inverts the spindle enable pin from low-disabled/high-enabled to low-enabled/high-disabled. Useful
// for some pre-built electronic boards.
// NOTE: If VARIABLE_SPINDLE is enabled(default), this option has no effect as the PWM output and
// spindle enable are combined to one pin. If you need both this option and spindle speed PWM,
// uncomment the config option USE_SPINDLE_DIR_AS_ENABLE_PIN below.
// 翻转主轴控制引脚, 从低-禁止/高-使能 改成 低-使能/高-禁止. 适用于一些已经做好的电子板.
// 注意: 如果使能了默认的VARIABLE_SPINDLE, 这个选项无效, 因为PWM输出和主轴使能端是共用一个引脚的. 如果你需要
// 打开这个选项,同时也打开主轴的速度PWM, 请去掉USE_SPINDLE_DIR_AS_ENABLE_PIN的注释

// #define INVERT_SPINDLE_ENABLE_PIN // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// Enable control pin states feedback in status reports. The data is presented as simple binary of
// the control pin port (0 (low) or 1(high)), masked to show only the input pins. Non-control pins on the
// port will always show a 0 value. See cpu_map.h for the pin bitmap. As with the limit pin reporting,
// we do not recommend keeping this option enabled. Try to only use this for setting up a new CNC.
// 使能状态报告中的控制引脚状态反馈. 数据是控制引脚端口的二进制值(0低, 1高), 被掩码后,只显示输入引脚. 在这个端口的
// 非控制引脚总是显示0值. 参考cpu_map.h的引脚位图. 和限位器引脚报告一样, 我们不推荐使能这个选项,
// 只在设置新的CNC中尝试这个选项.

// #define REPORT_CONTROL_PIN_STATE // Default disabled. Uncomment to enable.


// When Grbl powers-cycles or is hard reset with the Arduino reset button, Grbl boots up with no ALARM
// by default. This is to make it as simple as possible for new users to start using Grbl. When homing
// is enabled and a user has installed limit switches, Grbl will boot up in an ALARM state to indicate
// Grbl doesn't know its position and to force the user to home before proceeding. This option forces
// Grbl to always initialize into an ALARM state regardless of homing or not. This option is more for
// OEMs and LinuxCNC users that would like this power-cycle behavior.
// 当上电时,或者使用Arduino的复位按钮进行硬件复位时, grbl默认启动时没有警报. 这样做是为了尽可能简单的让新
// 手开始使用grbl. 当使能了返航, 用户装了限位开关后, grbl 将在警报状态中启动, 提示grbl还不清楚自己的位置,
// 并强制用户在工作前进行返航. 这个选项强制grbl不论是否返航,总是初始化后进入警报状态.
// 这个选项主要是给OEM和LinuxCNC用户使用,它们喜欢这种上电时的行为

// #define FORCE_INITIALIZATION_ALARM // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// ---------------------------------------------------------------------------------------
// ADVANCED CONFIGURATION OPTIONS:
// 高级配置选项:


// Enables minimal reporting feedback mode for GUIs, where human-readable strings are not as important.
// This saves nearly 2KB of flash space and may allow enough space to install other/future features.
// GUIs will need to install a look-up table for the error-codes that Grbl sends back in their place.
// NOTE: This feature is new and experimental. Make sure the GUI you are using supports this mode.
// 使能给GUI的最小报告反馈模式, 这时人类可读的字符串不重要了. 这个选项节省了大约2KB 代码空间, 允许足够多的
// 空间安装别的特征. GUI需要一个查找表来分析grbl发送给它的错误代码.
// 注意: 这是个新的实验性的特征, 确保你使用的GUI支持这个模式

// #define REPORT_GUI_MODE // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// The temporal resolution of the acceleration management subsystem. A higher number gives smoother
// acceleration, particularly noticeable on machines that run at very high feedrates, but may negatively
// impact performance. The correct value for this parameter is machine dependent, so it's advised to
// set this only as high as needed. Approximate successful values can widely range from 50 to 200 or more.
// NOTE: Changing this value also changes the execution time of a segment in the step segment buffer.
// When increasing this value, this stores less overall time in the segment buffer and vice versa. Make
// certain the step segment buffer is increased/decreased to account for these changes.
// 加速管理子系统的临时分辨率. 较高的数字得到更加平滑的加速度,当机器运行的进给速度非常高时,这点非常明显, 但会降低
// 系统的性能. 这个参数正确的值与机器有关, 因此建议设置得满足需求即可. 可用的值范围大概在50到200左右.
// 注意: 改变这个值,夜改变了在不久线段缓存里一个线段的执行时间.
// 当增加这个值时, 在线段缓存里保存了更少的全部执行时间. 反之亦然. 确保步进线段缓存也做了相应的 增加/减少 .
#define ACCELERATION_TICKS_PER_SECOND 100

// Adaptive Multi-Axis Step Smoothing (AMASS) is an advanced feature that does what its name implies,
// smoothing the stepping of multi-axis motions. This feature smooths motion particularly at low step
// frequencies below 10kHz, where the aliasing between axes of multi-axis motions can cause audible
// noise and shake your machine. At even lower step frequencies, AMASS adapts and provides even better
// step smoothing. See stepper.c for more details on the AMASS system works.
// 适应多轴步进平滑算法AMASS, 是一个高级的特征,如它名字所揭示的, 平滑多轴运动的步进. 这个特征可以平滑运动, 特别
// 是那些低于10khz的低步进运动, 因为这时, 在多轴运动时,每个轴之间的混淆会造成人类可以听到的噪声,以及机器的震动.
// 在更低的步进频率, AMASS进行适应并提供了更加好的步进平滑. AMASS系统的工作细节请参考stepper.c
#define ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING  // 默认使能, 取消注释禁止 Default enabled. Comment to disable.

// Sets the maximum step rate allowed to be written as a Grbl setting. This option enables an error
// check in the settings module to prevent settings values that will exceed this limitation. The maximum
// step rate is strictly limited by the CPU speed and will change if something other than an AVR running
// at 16MHz is used.
// 设置最大的被允许的步进速度,这个值会被写入grbl设定值. 这个选项使能了在设定模块内的一个错误检测, 防止设定值超过这个限制.
// 最大步进速度完全被CPU的速度限制, 如果不是16MHz的AVR运行这个系统, 需要改成别的值
// NOTE: For now disabled, will enable if flash space permits.
// 注意: 现在是禁止的. 如果代码空间允许,可以使能
// #define MAX_STEP_RATE_HZ 30000 // Hz

// By default, Grbl sets all input pins to normal-high operation with their internal pull-up resistors
// enabled. This simplifies the wiring for users by requiring only a switch connected to ground,
// although its recommended that users take the extra step of wiring in low-pass filter to reduce
// electrical noise detected by the pin. If the user inverts the pin in Grbl settings, this just flips
// which high or low reading indicates an active signal. In normal operation, this means the user
// needs to connect a normal-open switch, but if inverted, this means the user should connect a
// normal-closed switch.
// grbl默认会把所有输入引脚设置成常高操作, 并使能内部上拉电阻. 这简化了用户连线的,因为只要把开关接地就可以了.
// 尽管推荐用户额外加入一个低通滤波器来减少引脚的电噪声. 如果用户在grbl里翻转了引脚了, 它翻转后的高或低读数
// 提示了一个活动的信号. 在正常操作时, 这意味着用户需要连接一个常开的开关, 但是,如果翻转了, 这意味着用户应该
// 连接一个常闭的开关 .

// The following options disable the internal pull-up resistors, sets the pins to a normal-low
// operation, and switches must be now connect to Vcc instead of ground. This also flips the meaning
// of the invert pin Grbl setting, where an inverted setting now means the user should connect a
// normal-open switch and vice versa.
// 后面的选项禁止了内部上拉电阻,把引脚设置成一个常低操作, 开关必须连接到VCC而不是GND, 它也翻转了grbl的设定, 
// 一个翻转了的设定值现在意味着, 用户应该连接一个常开的开关.
//
// NOTE: All pins associated with the feature are disabled, i.e. XYZ limit pins, not individual axes.
// WARNING: When the pull-ups are disabled, this requires additional wiring with pull-down resistors!
// 注意: 所有和这个特征相连的引脚都被禁止了. 例如, XYZ限位引脚, 不是单独的轴.
// 警告: 当上拉电阻被禁止, 它需要额外的下拉电阻!

//#define DISABLE_LIMIT_PIN_PULL_UP
//#define DISABLE_PROBE_PIN_PULL_UP
//#define DISABLE_CONTROL_PIN_PULL_UP

// Sets which axis the tool length offset is applied. Assumes the spindle is always parallel with
// the selected axis with the tool oriented toward the negative direction. In other words, a positive
// tool length offset value is subtracted from the current location.
// 设置在哪个轴的上应用刀具长度偏置. 假设主轴总是和被选的轴平行,刀具安装这轴上,指向负数方向. 换句话说, 一个正的
// 刀具长度偏置值会被从当前的位置减去.

#define TOOL_LENGTH_OFFSET_AXIS Z_AXIS // 默认Z轴, 有效值为X, Y或Z轴 Default z-axis. Valid values are X_AXIS, Y_AXIS, or Z_AXIS.

// Enables variable spindle output voltage for different RPM values. On the Arduino Uno, the spindle
// enable pin will output 5V for maximum RPM with 256 intermediate levels and 0V when disabled.
// NOTE: IMPORTANT for Arduino Unos! When enabled, the Z-limit pin D11 and spindle enable pin D12 switch!
// The hardware PWM output on pin D11 is required for variable spindle output voltages.
// 使能为不同的RPM值输出可变主轴电压的变量. 在Arduino Uno里, 主轴使能引脚为最高RPM输出5V, 禁止主轴时输出0V,
// 2者中间有256级.
// 注意: 给Arduino Uno的重要提示! 当使能后, Z轴限位引脚D11和主轴使能引脚D12开关!
// 可变主轴输出电压需要D11引脚的PWM输出

#define VARIABLE_SPINDLE // 默认使能, 取消注释禁止 Default enabled. Comment to disable.

// Used by the variable spindle output only. These parameters set the maximum and minimum spindle speed
// "S" g-code values to correspond to the maximum and minimum pin voltages. There are 256 discrete and
// equally divided voltage bins between the maximum and minimum spindle speeds. So for a 5V pin, 1000
// max rpm, and 250 min rpm, the spindle output voltage would be set for the following "S" commands:
// "S1000" @ 5V, "S250" @ 0.02V, and "S625" @ 2.5V (mid-range). The pin outputs 0V when disabled.
// 仅供可变主轴输出使用. 这些参数把最大和最小的主轴速度 "S"g代码值,和最大和最小的引脚电压对应起来. 因此,对一个5V的引脚,
// 最大1000RMP, 最小250RPM, 主轴输出电压可以使用"S"命令这样设置:
// "S1000" @ 5V, "S250" @ 0.02V, and "S625" @ 2.5V (中间范围).当禁止后, 这个引脚输出0V

#define SPINDLE_MAX_RPM 1000.0 // 最大的主轴RPM, 这个值等于100%的占空比PWM  Max spindle RPM. This value is equal to 100% duty cycle on the PWM.
#define SPINDLE_MIN_RPM 0.0    // 最大的主轴RPM, 这个值等于1/256的占空比PWM Min spindle RPM. This value is equal to (1/256) duty cycle on the PWM.

// Used by variable spindle output only. This forces the PWM output to a minimum duty cycle when enabled.
// When disabled, the PWM pin will still read 0V. Most users will not need this option, but it may be
// useful in certain scenarios. This setting does not update the minimum spindle RPM calculations. Any
// spindle RPM output lower than this value will be set to this value.
// 仅供可变主轴输出使用. 当使能后, 它强制PWM输出一个最小的占空比周期. 当禁止后, PWM引脚读数还是为0V. 绝大多数用户
// 不需要这个选项, 但在某些特定场合它是有用的. 这个设定不更新最小主轴RPM计算. 任何低于这个值的主轴RPM输出会被设置成这个值

// #define MINIMUM_SPINDLE_PWM 5 // 默认使能, 取消注释禁止 Default disabled. Uncomment to enable. Integer (0-255)

// By default on a 328p(Uno), Grbl combines the variable spindle PWM and the enable into one pin to help
// preserve I/O pins. For certain setups, these may need to be separate pins. This configure option uses
// the spindle direction pin(D13) as a separate spindle enable pin along with spindle speed PWM on pin D11.
// NOTE: This configure option only works with VARIABLE_SPINDLE enabled and a 328p processor (Uno).
// NOTE: With no direction pin, the spindle clockwise M4 g-code command will be removed. M3 and M5 still work.
// NOTE: BEWARE! The Arduino bootloader toggles the D13 pin when it powers up. If you flash Grbl with
// a programmer (you can use a spare Arduino as "Arduino as ISP". Search the web on how to wire this.),
// this D13 LED toggling should go away. We haven't tested this though. Please report how it goes!
// 在328p(Uno)上, grbl默认把可变主轴PWM和使能信号共享一个引脚,节省IO. 对某些设置, 也许需要各自的引脚. 这个
// 配置选项使用了主轴的方向引脚(D13), 作为一个单独的主轴使能引脚,主轴速度PWM在引脚D11.
// 注意: 这个选项仅在VARIABLE_SPINDLE使能后的328p(Uno)上起作用
// 注意: 如果没有方向引脚, 主轴逆时针M4 g代码将被移去, M3和M5继续可以工作.
// 注意: 小心! Arudino bootloader在上电时翻转了D13引脚. 如果你重新烧录了grbl(你可以使用另一个Arduino当作ISP下载), 
// D13 LED翻转功能会消失. 我们还没测试这个. 请告知它是如何消失的!


// #define USE_SPINDLE_DIR_AS_ENABLE_PIN // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// With this enabled, Grbl sends back an echo of the line it has received, which has been pre-parsed (spaces
// removed, capitalized letters, no comments) and is to be immediately executed by Grbl. Echoes will not be
// sent upon a line buffer overflow, but should for all normal lines sent to Grbl. For example, if a user
// sendss the line 'g1 x1.032 y2.45 (test comment)', Grbl will echo back in the form '[echo: G1X1.032Y2.45]'.
// NOTE: Only use this for debugging purposes!! When echoing, this takes up valuable resources and can effect
// performance. If absolutely needed for normal operation, the serial write buffer should be greatly increased
// to help minimize transmission waiting within the serial write protocol.
// 当这个被使能后, grbl会把她接受到的命令发送回去, 这个命令已经被预处理了(移去空格, 全部大写字符, 没有注释),并且可以
// 立即被grbl执行. 当命令行缓存溢出,就不会回应, 但正常的情况下都会回应.例如, 如果一个用户发送了一行'g1 x1.032 y2.45 (test comment)'
// grbl 会回应 '[echo: G1X1.032Y2.45]'. 
// 注意: 仅供调试使用!! 回送命令,消耗了太多的宝贵的资源,并且影响了性能. 如果在正常操作中绝对需要这个功能, 必须增加串口发送缓冲区的长度,
// 最小化串口发送协议处理时的等待时间

// #define REPORT_ECHO_LINE_RECEIVED // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// Minimum planner junction speed. Sets the default minimum junction speed the planner plans to at
// every buffer block junction, except for starting from rest and end of the buffer, which are always
// zero. This value controls how fast the machine moves through junctions with no regard for acceleration
// limits or angle between neighboring block line move directions. This is useful for machines that can't
// tolerate the tool dwelling for a split second, i.e. 3d printers or laser cutters. If used, this value
// should not be much greater than zero or to the minimum value necessary for the machine to work.
// 最小化规划器交叉点速度, 设置最小的交叉点速度,规划器会用在每个缓存程序段的交叉点上,除了复位后第七十点和缓存区的终点,
// 这2个点总是为零. 这个值控制着机器,在不考虑加速度限制和相邻程序段直线移动方向的前提下,以多快的速度移过交叉点. 这个选项对不能容忍
// 刀具暂停的机器是有用的, 例如, 3D打印机或激光剪切机. 如果使用了它, 这个值不会比零大多少, 或者设置成机器必须工作的最小值.
#define MINIMUM_JUNCTION_SPEED 0.0 // (mm/min)

// Sets the minimum feed rate the planner will allow. Any value below it will be set to this minimum
// value. This also ensures that a planned motion always completes and accounts for any floating-point
// round-off errors. Although not recommended, a lower value than 1.0 mm/min will likely work in smaller
// machines, perhaps to 0.1mm/min, but your success may vary based on multiple factors.
// 设置规划器允许的最小进给速度. 任何比它小的值将会使用这个最小值. 它也确保一个被规划的运动总是完成了,并且对
// 任何浮点舍入错误负责
// 设置规划器允许的最小进给速度. 任何比它小的值将会使用这个最小值. 它也确保一个被规划的运动总是完成了,并且对
// 任何浮点舍入错误负责。尽管不推荐，可以在一个较小的机器上，一个比  1.0mm/分钟 小的值，也许是 0.1mm/分钟，
// 但成功与否取决于多个因素
#define MINIMUM_FEED_RATE 1.0 // (mm/min)

// Number of arc generation iterations by small angle approximation before exact arc trajectory
// correction with expensive sin() and cos() calcualtions. This parameter maybe decreased if there
// are issues with the accuracy of the arc generations, or increased if arc execution is getting
// bogged down by too many trig calculations.
// 在使用复杂的sin()和cos()进行精确的圆弧轨迹校正前, 使用小角度近似法所使用的圆弧生成的迭代数量. 
// 如果圆弧生成的精度发生问题,这个参数可以被降低, 如果太多三角计算拉低了性能,参数可以增加
#define N_ARC_CORRECTION 12 // Integer (1-255)

// The arc G2/3 g-code standard is problematic by definition. Radius-based arcs have horrible numerical
// errors when arc at semi-circles(pi) or full-circles(2*pi). Offset-based arcs are much more accurate
// but still have a problem when arcs are full-circles (2*pi). This define accounts for the floating
// point issues when offset-based arcs are commanded as full circles, but get interpreted as extremely
// small arcs with around machine epsilon (1.2e-7rad) due to numerical round-off and precision issues.
// This define value sets the machine epsilon cutoff to determine if the arc is a full-circle or not.
// NOTE: Be very careful when adjusting this value. It should always be greater than 1.2e-7 but not too
// much greater than this. The default setting should capture most, if not all, full arc error situations.
// g代码标准对圆弧G2/3的定义是有问题的. 基于半径的圆弧, 在圆弧是半圆形(pi)或整圆(2*pi)时,有可怕的数值错误. 基于
// 偏置的圆弧比较精确, 但在整圆(2*pi)时还是有错误. 当基于偏置的圆弧被当作全圆时,这个定义导致了浮点问题, 由于
// 数值舍入和精度的原因,这个圆被当成一个接近机器epsilon(1.2e-7弧度)的一个非常小的圆弧. 这个定义值设置了机器
// 的epsilon截止值, 来确定这个圆弧究竟是不是一个全圆.
// 注意: 调整这个值时需要非常小心. 必须总是比1.2e-7大, 但不要大太多. 默认设置应该可以覆盖绝大多数或全部圆弧错误情况,

#define ARC_ANGULAR_TRAVEL_EPSILON 5E-7 // 浮点(弧度) Float (radians)

// Time delay increments performed during a dwell. The default value is set at 50ms, which provides
// a maximum time delay of roughly 55 minutes, more than enough for most any application. Increasing
// this delay will increase the maximum dwell time linearly, but also reduces the responsiveness of
// run-time command executions, like status reports, since these are performed between each dwell
// time step. Also, keep in mind that the Arduino delay timer is not very accurate for long delays.
// 在暂停时的时间延迟增量. 默认值是50毫秒, 这可以提供大概55分钟的最大延迟时间, 足够绝大多数系统使用.
// 增大这个值,也会线性的增加最大暂停时间, 但也降低了实时命令执行的反应速度, 比如状态报告, 因为是在
// 每个暂停时间之间执行它的. 另外,记住,Arduino延时计时器对长延时不是很精确

#define DWELL_TIME_STEP 50 // 整数(1-255)(毫秒) Integer (1-255) (milliseconds)

// Creates a delay between the direction pin setting and corresponding step pulse by creating
// another interrupt (Timer2 compare) to manage it. The main Grbl interrupt (Timer1 compare)
// sets the direction pins, and does not immediately set the stepper pins, as it would in
// normal operation. The Timer2 compare fires next to set the stepper pins after the step
// pulse delay time, and Timer2 overflow will complete the step pulse, except now delayed
// by the step pulse time plus the step pulse delay. (Thanks langwadt for the idea!)
// NOTE: Uncomment to enable. The recommended delay must be > 3us, and, when added with the
// user-supplied step pulse time, the total time must not exceed 127us. Reported successful
// values for certain setups have ranged from 5 to 20us.
// 在方向引脚设置和相应的步进脉冲之间加入一个延迟, 需要使用另一个中断 (Timer2 比较)来管理它. 主grbl中断
// (Timer1 比较)设置方向引脚, 然后不会像正常操作一样立即设置步进引脚, 在这个延迟后, Timer2 COMOPARE中断触发,设置
// 步进引脚, Timer2 OVF中断将完成这个步进脉冲, 只不过现在是延迟了步进脉冲的时间加上步进脉冲延迟的时间. (谢谢langwadt的主意!)
// 注意: 去掉注释可以使能, 推荐的延时必须大于3微秒, 而且,当家人了用户提供的步进脉冲时间, 总共时间不能
// 超过127微秒. 对一些设置,得到的反馈是这个值在5到20微秒之间


// #define STEP_PULSE_DELAY 10 // 步进脉冲延迟, 微秒, 默认禁止 Step pulse delay in microseconds. Default disabled.

// The number of linear motions in the planner buffer to be planned at any give time. The vast
// majority of RAM that Grbl uses is based on this buffer size. Only increase if there is extra
// available RAM, like when re-compiling for a Mega or Sanguino. Or decrease if the Arduino
// begins to crash due to the lack of available RAM or if the CPU is having trouble keeping
// up with planning new incoming motions as they are executed.
// 在任何时候,在规划器缓存准备被规划的线性运动的数量. grbl主要的RAM用在这个缓存上了. 仅在还有多余可用的RAM时
// 例如当重新为Mega或Sanguino编译grbl时才增加这个值. 当grbl开始因为缺少RAM而崩溃时,或CPU在执行运动
// 时不能处理新收到的运动数据时, 降低这个值

// #define BLOCK_BUFFER_SIZE 18  // 去掉注释后可以覆盖在planner.h的默认值 Uncomment to override default in planner.h.

// Governs the size of the intermediary step segment buffer between the step execution algorithm
// and the planner blocks. Each segment is set of steps executed at a constant velocity over a
// fixed time defined by ACCELERATION_TICKS_PER_SECOND. They are computed such that the planner
// block velocity profile is traced exactly. The size of this buffer governs how much step
// execution lead time there is for other Grbl processes have to compute and do their thing
// before having to come back and refill this buffer, currently at ~50msec of step moves.
// 管理在步进执行算法和规划器程序段之间的中间步数线段缓存的长度. 每个线段是一个步数的集合, 步数以恒定的速度运行
// 一段固定的时间,这个时间由ACCELERATION_TICKS_PER_SECOND定义. 它们被计算从而规划器程序段的速度剖面图可以被
// 严密的追踪.这个缓存的长度决定了, 在其他grbl需要计算然后在返回前处理它们的事物的处理函数并填充缓存前, 这里有多少执行提前量
// 当前是设置在大约50毫秒 
// #define SEGMENT_BUFFER_SIZE 6 // 去掉注释后可以覆盖在stepper.h的默认值  Uncomment to override default in stepper.h.

// Line buffer size from the serial input stream to be executed. Also, governs the size of
// each of the startup blocks, as they are each stored as a string of this size. Make sure
// to account for the available EEPROM at the defined memory address in settings.h and for
// the number of desired startup blocks.
// 串口输入流利要被执行的直线缓存的长度. 另外,决定了每个启动程序段的长度, 因为它们保存为这个长度的字符串.
// 确保在settings.h说明了可用的EEPROM和所需的启动程序段的数量.

// NOTE: 80 characters is not a problem except for extreme cases, but the line buffer size
// can be too small and g-code blocks can get truncated. Officially, the g-code standards
// support up to 256 characters. In future versions, this default will be increased, when
// we know how much extra memory space we can re-invest into this.
// 注意: 除了极端情况,80个字符够用了,但命令缓存长度可能回太小导致g代码程序段被截断. g代码标准
// 官方支持256个字符. 在未来版本里,当我们知道有多少额外的RAM可以用在这上面时, 这个默认值会加大, 

// #define LINE_BUFFER_SIZE 80  // 去掉注释后可以覆盖在protocol.h的默认值  Uncomment to override default in protocol.h

// Serial send and receive buffer size. The receive buffer is often used as another streaming
// buffer to store incoming blocks to be processed by Grbl when its ready. Most streaming
// interfaces will character count and track each block send to each block response. So,
// increase the receive buffer if a deeper receive buffer is needed for streaming and avaiable
// memory allows. The send buffer primarily handles messages in Grbl. Only increase if large
// messages are sent and Grbl begins to stall, waiting to send the rest of the message.
// 串口发送和接收缓存的长度. 接收缓存常常被用着第二个缓存,用来保存接收的程序段供grbl处理. 绝大多数字符流接口
// 是字符数字,已经跟踪每个程序段发送每个程序段的相应. 因此, 如果需要字符流有更深的接收缓存,而且有多余可用的RAM,
// 可以增加接收缓存的长度. 发送缓存主要处理grbl的消息, 如果发送长消息是grbl开始变慢,等待发送消息的余下部分时,可以
// 增加发送缓存长度.

// NOTE: Buffer size values must be greater than zero and less than 256.
// 注意: 缓存长度值必须大于0小于256

// #define RX_BUFFER_SIZE 128 // 去掉注释后可以覆盖在serial.h的默认值  Uncomment to override defaults in serial.h
// #define TX_BUFFER_SIZE 64

// Toggles XON/XOFF software flow control for serial communications. Not officially supported
// due to problems involving the Atmega8U2 USB-to-serial chips on current Arduinos. The firmware
// on these chips do not support XON/XOFF flow control characters and the intermediate buffer
// in the chips cause latency and overflow problems with standard terminal programs. However,
// using specifically-programmed UI's to manage this latency problem has been confirmed to work.
// As well as, older FTDI FT232RL-based Arduinos(Duemilanove) are known to work with standard
// terminal programs since their firmware correctly manage these XON/XOFF characters. In any
// case, please report any successes to grbl administrators!
// 翻转串口通讯的XON/XOFF软件流控制. 没有正式支持,因为当前的Arduino使用的Atmega8U2 USB-串口 芯片有问题.
// 这些芯片上的固件不支持 XON/XOFF流控制字符, 这些芯片上的中间缓存导致了一个潜伏期, 当和标准的终端软件使用时,
// 导致了溢出问题,然而, 使用特定的UI来管理这个潜伏期已经被证明可以工作. 还有, 旧的Arduinos(Duemilanove)使用
// FTDI FT232RL, 它可以和标准的终端软件工作,因为它们的固件正确的管理的这些XON/XOFF字符. 在任何情况下,
// 请向grbl管理员报告成功的情况.

// #define ENABLE_XONXOFF //默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// A simple software debouncing feature for hard limit switches. When enabled, the interrupt
// monitoring the hard limit switch pins will enable the Arduino's watchdog timer to re-check
// the limit pin state after a delay of about 32msec. This can help with CNC machines with
// problematic false triggering of their hard limit switches, but it WILL NOT fix issues with
// electrical interference on the signal cables from external sources. It's recommended to first
// use shielded signal cables with their shielding connected to ground (old USB/computer cables
// work well and are cheap to find) and wire in a low-pass circuit into each limit pin.
// 硬件限位开关的一个简单的软件去抖特征. 当使能后, 监视硬件限位开关引脚的中断将使能Arduino的看门狗时钟,
// 在大约32毫秒的延时后, 重新检查限位引脚的状态. 这可以帮助CNC机器改善它们的硬件限位中断的问题重重的虚假触发.
// 但*不能*修复从外部通过信号线接进来的问题. 推荐先使用屏蔽信号线,屏蔽层接地(旧的USB电线效果不错也好找),
// 然后在每个限位引脚加入一个低通滤波电路.

// #define ENABLE_SOFTWARE_DEBOUNCE // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.

// Force Grbl to check the state of the hard limit switches when the processor detects a pin
// change inside the hard limit ISR routine. By default, Grbl will trigger the hard limits
// alarm upon any pin change, since bouncing switches can cause a state check like this to
// misread the pin. When hard limits are triggered, they should be 100% reliable, which is the
// reason that this option is disabled by default. Only if your system/electronics can guarantee
// that the switches don't bounce, we recommend enabling this option. This will help prevent
// triggering a hard limit when the machine disengages from the switch.
// 当处理器在硬件限位ISR处理过程内探测到一个引脚发生了改变,强制grbl检查硬件限位器的状态. grbl默认任何限位引脚发生变化,将触发硬件限位警报, 
// 因为抖动的开关可能导致一个类似这样的状态检测, 从而误读引脚. 当触发了硬件限位引脚, 它们必须100%可靠, 这就是
// 默认禁止这个开关的原因. 仅在你的系统/电路 能保证开关不会跳动时, 我们才推荐你使能这个选项. 这可以防止当机器脱离
// 限位开关是触发一个硬件限位.

// NOTE: This option has no effect if SOFTWARE_DEBOUNCE is enabled.
// 注意: 如果SOFTWARE_DEBOUNCE被使能,这个选项不起作用

// #define HARD_LIMIT_FORCE_STATE_CHECK // 默认禁止, 取消注释使能 Default disabled. Uncomment to enable.


// ---------------------------------------------------------------------------------------
// COMPILE-TIME ERROR CHECKING OF DEFINE VALUES:
// 对定义值的编译错误进行检测

#ifndef HOMING_CYCLE_0
#error "Required HOMING_CYCLE_0 not defined."
#endif

#if defined(USE_SPINDLE_DIR_AS_ENABLE_PIN) && !defined(VARIABLE_SPINDLE)
#error "USE_SPINDLE_DIR_AS_ENABLE_PIN may only be used with VARIABLE_SPINDLE enabled"
#endif

#if defined(USE_SPINDLE_DIR_AS_ENABLE_PIN) && !defined(CPU_MAP_ATMEGA328P)
#error "USE_SPINDLE_DIR_AS_ENABLE_PIN may only be used with a 328p processor"
#endif

// ---------------------------------------------------------------------------------------


#endif
