/**
 * v9.4.0-dev 的配置文件
 */

/*
 * Copy this file as `lv_conf.h`
 * 1. simply next to `lvgl` folder
 * 2. or to any other place and
 *    - define `LV_CONF_INCLUDE_SIMPLE`;
 *    - add the path as an include path.
 */
/*
 * 复制此文件为 `lv_conf.h`
 * 1. 简单地放在 `lvgl` 文件夹旁边
 * 2. 或者放到任何其他地方并且
 *    - 定义 `LV_CONF_INCLUDE_SIMPLE`；
 *    - 添加路径作为包含路径。
 */

/* clang-format off */
#if 1 /* Enable content */
#ifndef LV_CONF_H
#define LV_CONF_H

/* If you need to include anything here, do it inside the `__ASSEMBLY__` guard */
/* 如果您需要在此处包含任何内容，请在 `__ASSEMBLY__` 保护内进行 */
#if  0 && defined(__ASSEMBLY__)
#include "my_include.h"
#endif

/*====================
   COLOR SETTINGS
 *====================*/
/*====================
   颜色设置
 *====================*/

/** Color depth: 1 (I1), 8 (L8), 16 (RGB565), 24 (RGB888), 32 (XRGB8888) */
/** 颜色深度：1 (I1), 8 (L8), 16 (RGB565), 24 (RGB888), 32 (XRGB8888) */
#define LV_COLOR_DEPTH 16

/*=========================
   STDLIB WRAPPER SETTINGS
 *=========================*/
/*=========================
   标准库包装器设置
 *=========================*/

/** Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
/** 可能的值
 * - LV_STDLIB_BUILTIN:     LVGL 的内置实现
 * - LV_STDLIB_CLIB:        标准 C 函数，如 malloc、strlen 等
 * - LV_STDLIB_MICROPYTHON: MicroPython 实现
 * - LV_STDLIB_RTTHREAD:    RT-Thread 实现
 * - LV_STDLIB_CUSTOM:      外部实现这些函数
 */
#define LV_USE_STDLIB_MALLOC    LV_STDLIB_CLIB

/** Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
/** 可能的值
 * - LV_STDLIB_BUILTIN:     LVGL 的内置实现
 * - LV_STDLIB_CLIB:        标准 C 函数，如 malloc、strlen 等
 * - LV_STDLIB_MICROPYTHON: MicroPython 实现
 * - LV_STDLIB_RTTHREAD:    RT-Thread 实现
 * - LV_STDLIB_CUSTOM:      外部实现这些函数
 */
#define LV_USE_STDLIB_STRING    LV_STDLIB_CLIB

/** Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
/** 可能的值
 * - LV_STDLIB_BUILTIN:     LVGL 的内置实现
 * - LV_STDLIB_CLIB:        标准 C 函数，如 malloc、strlen 等
 * - LV_STDLIB_MICROPYTHON: MicroPython 实现
 * - LV_STDLIB_RTTHREAD:    RT-Thread 实现
 * - LV_STDLIB_CUSTOM:      外部实现这些函数
 */
#define LV_USE_STDLIB_SPRINTF   LV_STDLIB_CLIB

#define LV_STDINT_INCLUDE       <stdint.h>
#define LV_STDDEF_INCLUDE       <stddef.h>
#define LV_STDBOOL_INCLUDE      <stdbool.h>
#define LV_INTTYPES_INCLUDE     <inttypes.h>
#define LV_LIMITS_INCLUDE       <limits.h>
#define LV_STDARG_INCLUDE       <stdarg.h>

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
    /** Size of memory available for `lv_malloc()` in bytes (>= 2kB) */
    /** `lv_malloc()` 可用内存大小（字节）（>= 2kB） */
    #define LV_MEM_SIZE (64 * 1024U)          /**< [bytes] */

    /** Size of the memory expand for `lv_malloc()` in bytes */
    /** `lv_malloc()` 内存扩展大小（字节） */
    #define LV_MEM_POOL_EXPAND_SIZE 0

    /** Set an address for the memory pool instead of allocating it as a normal array. Can be in external SRAM too. */
    /** 为内存池设置地址，而不是将其分配为普通数组。也可以在外部 SRAM 中。 */
    #define LV_MEM_ADR 0     /**< 0: unused*/
    /* Instead of an address give a memory allocator that will be called to get a memory pool for LVGL. E.g. my_malloc */
    /* 不是给出地址，而是给出一个内存分配器，它将被调用来为 LVGL 获取内存池。例如 my_malloc */
    #if LV_MEM_ADR == 0
        #undef LV_MEM_POOL_INCLUDE
        #undef LV_MEM_POOL_ALLOC
    #endif
#endif  /*LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN*/

/*====================
   HAL SETTINGS
 *====================*/
/*====================
   HAL 设置
 *====================*/

/** Default display refresh, input device read and animation step period. */
/** 默认显示刷新、输入设备读取和动画步进周期。 */
/** 刷新率,FPS */
#define LV_DEF_REFR_PERIOD  1      /**< [ms] */

/** Default Dots Per Inch. Used to initialize default sizes such as widgets sized, style paddings.
 * (Not so important, you can adjust it to modify default sizes and spaces.) */
/** 默认每英寸点数。用于初始化默认大小，如小部件大小、样式填充。
 * （不太重要，您可以调整它来修改默认大小和空间。） */
#define LV_DPI_DEF 123              /**< [px/inch] */

/*=================
 * OPERATING SYSTEM
 *=================*/
/*=================
 * 操作系统
 *=================*/
/** Select operating system to use. Possible options:
 * - LV_OS_NONE
 * - LV_OS_PTHREAD
 * - LV_OS_FREERTOS
 * - LV_OS_CMSIS_RTOS2
 * - LV_OS_RTTHREAD
 * - LV_OS_WINDOWS
 * - LV_OS_MQX
 * - LV_OS_SDL2
 * - LV_OS_CUSTOM */
/** 选择要使用的操作系统。可能的选项：
 * - LV_OS_NONE
 * - LV_OS_PTHREAD
 * - LV_OS_FREERTOS
 * - LV_OS_CMSIS_RTOS2
 * - LV_OS_RTTHREAD
 * - LV_OS_WINDOWS
 * - LV_OS_MQX
 * - LV_OS_SDL2
 * - LV_OS_CUSTOM */
#define LV_USE_OS   LV_OS_PTHREAD

#if LV_USE_OS == LV_OS_CUSTOM
    #define LV_OS_CUSTOM_INCLUDE <stdint.h>
#endif
#if LV_USE_OS == LV_OS_FREERTOS
    /*
     * Unblocking an RTOS task with a direct notification is 45% faster and uses less RAM
     * than unblocking a task using an intermediary object such as a binary semaphore.
     * RTOS task notifications can only be used when there is only one task that can be the recipient of the event.
     */
    /*
     * 使用直接通知来解除 RTOS 任务阻塞比使用中间对象（如二进制信号量）来解除任务阻塞快 45% 并且使用更少的 RAM。
     * RTOS 任务通知只能在只有一个任务可以成为事件接收者时使用。
     */
    #define LV_USE_FREERTOS_TASK_NOTIFY 1
#endif

/*========================
 * RENDERING CONFIGURATION
 *========================*/
/*========================
 * 渲染配置
 *========================*/

/** Align stride of all layers and images to this bytes */
/** 将所有层和图像的步幅对齐到此字节数 */
#define LV_DRAW_BUF_STRIDE_ALIGN                1

/** Align start address of draw_buf addresses to this bytes*/
/** 将 draw_buf 地址的起始地址对齐到此字节数 */
#define LV_DRAW_BUF_ALIGN                       4

/** Using matrix for transformations.
 * Requirements:
 * - `LV_USE_MATRIX = 1`.
 * - Rendering engine needs to support 3x3 matrix transformations. */
/** 使用矩阵进行变换。
 * 要求：
 * - `LV_USE_MATRIX = 1`。
 * - 渲染引擎需要支持 3x3 矩阵变换。 */
#define LV_DRAW_TRANSFORM_USE_MATRIX            0

/* If a widget has `style_opa < 255` (not `bg_opa`, `text_opa` etc) or not NORMAL blend mode
 * it is buffered into a "simple" layer before rendering. The widget can be buffered in smaller chunks.
 * "Transformed layers" (if `transform_angle/zoom` are set) use larger buffers
 * and can't be drawn in chunks. */
/* 如果小部件的 `style_opa < 255`（不是 `bg_opa`、`text_opa` 等）或不是 NORMAL 混合模式
 * 则在渲染之前会被缓冲到“简单”层。小部件可以分块缓冲。
 * “变换层”（如果设置了 `transform_angle/zoom`）会使用更大的缓冲区，且无法分块绘制。*/
/* 如果小部件的 `style_opa < 255`（不是 `bg_opa`、`text_opa` 等）或不是 NORMAL 混合模式
 * 则在渲染之前将其缓冲到"简单"层中。小部件可以被缓冲为更小的块。
 * "变换层"（如果设置了 `transform_angle/zoom`）使用更大的缓冲区
 * 并且无法分块绘制。 */

/** The target buffer size for simple layer chunks. */
/** 简单层块的目标缓冲区大小。 */
#define LV_DRAW_LAYER_SIMPLE_BUF_SIZE    (60*1024 * 1024)    /**< [bytes]*/

/* Limit the max allocated memory for simple and transformed layers.
 * It should be at least `LV_DRAW_LAYER_SIMPLE_BUF_SIZE` sized but if transformed layers are also used
 * it should be enough to store the largest widget too (width x height x 4 area).
 * Set it to 0 to have no limit. */
/* 限制简单层和变换层的最大分配内存。
 * 至少应为 `LV_DRAW_LAYER_SIMPLE_BUF_SIZE` 大小，如果使用变换层，
 * 还应能容纳最大的小部件（宽 x 高 x 4 区域）。
 * 设置为 0 表示不限制。*/
/* 限制简单层和变换层的最大分配内存。
 * 它应该至少有 `LV_DRAW_LAYER_SIMPLE_BUF_SIZE` 大小，但如果也使用变换层
 * 它应该足够存储最大的小部件（宽度 x 高度 x 4 区域）。
 * 设置为 0 表示没有限制。 */
#define LV_DRAW_LAYER_MAX_MEMORY 0  /**< No limit by default [bytes]*/

/** Stack size of drawing thread.
 * NOTE: If FreeType or ThorVG is enabled, it is recommended to set it to 32KB or more.
 */
/** 绘制线程的堆栈大小。
 * 注意：如果启用 FreeType 或 ThorVG，建议设置为 32KB 或更大。
 */
/** 绘制线程的堆栈大小。
 * 注意：如果启用了 FreeType 或 ThorVG，建议将其设置为 32KB 或更多。
 */
#define LV_DRAW_THREAD_STACK_SIZE    (60*1024 * 1024)         /**< [bytes]*/

/** Thread priority of the drawing task.
 *  Higher values mean higher priority.
 *  Can use values from lv_thread_prio_t enum in lv_os.h: LV_THREAD_PRIO_LOWEST,
 *  LV_THREAD_PRIO_LOW, LV_THREAD_PRIO_MID, LV_THREAD_PRIO_HIGH, LV_THREAD_PRIO_HIGHEST
 *  Make sure the priority value aligns with the OS-specific priority levels.
 *  On systems with limited priority levels (e.g., FreeRTOS), a higher value can improve
 *  rendering performance but might cause other tasks to starve. */
/** 绘制任务的线程优先级。
 *  值越高表示优先级越高。
 *  可以使用 lv_os.h 中 lv_thread_prio_t 枚举的值：LV_THREAD_PRIO_LOWEST、
 *  LV_THREAD_PRIO_LOW、LV_THREAD_PRIO_MID、LV_THREAD_PRIO_HIGH、LV_THREAD_PRIO_HIGHEST
 *  确保优先级值与特定于操作系统的优先级级别对齐。
 *  在优先级级别有限的系统（例如 FreeRTOS）上，较高的值可以提高
 *  渲染性能，但可能会导致其他任务“饥饿”。 */
// #define LV_DRAW_THREAD_PRIO LV_THREAD_PRIO_HIGH
#define LV_DRAW_THREAD_PRIO LV_THREAD_PRIO_HIGHEST

#define LV_USE_DRAW_SW 1
#if LV_USE_DRAW_SW == 1
    /*
     * Selectively disable color format support in order to reduce code size.
     * NOTE: some features use certain color formats internally, e.g.
     * - gradients use RGB888
     * - bitmaps with transparency may use ARGB8888
     */
    /*
     * 有选择地禁用颜色格式支持以减小代码大小。
     * 注意：某些功能内部使用某些颜色格式，例如
     * - 渐变使用 RGB888
     * - 带透明度的位图可能使用 ARGB8888
     */
    #define LV_DRAW_SW_SUPPORT_RGB565       1
    #define LV_DRAW_SW_SUPPORT_RGB565_SWAPPED       1
    #define LV_DRAW_SW_SUPPORT_RGB565A8     1
    #define LV_DRAW_SW_SUPPORT_RGB888       1
    #define LV_DRAW_SW_SUPPORT_XRGB8888     1
    #define LV_DRAW_SW_SUPPORT_ARGB8888     1
    #define LV_DRAW_SW_SUPPORT_ARGB8888_PREMULTIPLIED 1
    #define LV_DRAW_SW_SUPPORT_L8           1
    #define LV_DRAW_SW_SUPPORT_AL88         1
    #define LV_DRAW_SW_SUPPORT_A8           1
    #define LV_DRAW_SW_SUPPORT_I1           1

    /* The threshold of the luminance to consider a pixel as
     * active in indexed color format */
    /* 在索引颜色格式中，将像素视为活动的亮度阈值 */
    #define LV_DRAW_SW_I1_LUM_THRESHOLD 127

    /** Set number of draw units.
     *  - > 1 requires operating system to be enabled in `LV_USE_OS`.
     *  - > 1 means multiple threads will render the screen in parallel. */
    /** 设置绘制单元的数量。
     *  - > 1 需要在 `LV_USE_OS` 中启用操作系统。
     *  - > 1 意味着多个线程将并行渲染屏幕。 */
    //多线程!!
    #define LV_DRAW_SW_DRAW_UNIT_CNT    8

    /** Use Arm-2D to accelerate software (sw) rendering. */
    /** 使用 Arm-2D 加速软件 (sw) 渲染。 */
    #define LV_USE_DRAW_ARM2D_SYNC      0

    /** Enable native helium assembly to be compiled. */
    /** 启用原生 Helium 汇编进行编译。 */
    #define LV_USE_NATIVE_HELIUM_ASM    0

    /**
     * - 0: Use a simple renderer capable of drawing only simple rectangles with gradient, images, text, and straight lines only.
     * - 1: Use a complex renderer capable of drawing rounded corners, shadow, skew lines, and arcs too. */
    /**
     * - 0: 使用一个简单的渲染器，只能绘制带有渐变、图像、文本和直线的简单矩形。
     * - 1: 使用一个复杂的渲染器，也能绘制圆角、阴影、斜线和圆弧。 */
    #define LV_DRAW_SW_COMPLEX          1

    #if LV_DRAW_SW_COMPLEX == 1
        /** Allow buffering some shadow calculation.
         *  LV_DRAW_SW_SHADOW_CACHE_SIZE is the maximum shadow size to buffer, where shadow size is
         *  `shadow_width + radius`.  Caching has LV_DRAW_SW_SHADOW_CACHE_SIZE^2 RAM cost. */
        /** 允许缓存一些阴影计算。
         *  LV_DRAW_SW_SHADOW_CACHE_SIZE 是要缓存的最大阴影大小，其中阴影大小是
         *  `shadow_width + radius`。缓存的 RAM 开销为 LV_DRAW_SW_SHADOW_CACHE_SIZE^2。 */
        #define LV_DRAW_SW_SHADOW_CACHE_SIZE 0

        /** Set number of maximally-cached circle data.
         *  The circumference of 1/4 circle are saved for anti-aliasing.
         *  `radius * 4` bytes are used per circle (the most often used radiuses are saved).
         *  - 0: disables caching */
        /** 设置最大缓存圆数据的数量。
         *  保存 1/4 圆的周长用于抗锯齿。
         *  每个圆使用 `radius * 4` 字节（最常用的半径会被保存）。
         *  - 0：禁用缓存 */
        #define LV_DRAW_SW_CIRCLE_CACHE_SIZE 4
    #endif

    #define  LV_USE_DRAW_SW_ASM     LV_DRAW_SW_ASM_NONE

    #if LV_USE_DRAW_SW_ASM == LV_DRAW_SW_ASM_CUSTOM
        #define  LV_DRAW_SW_ASM_CUSTOM_INCLUDE ""
    #endif

    /** Enable drawing complex gradients in software: linear at an angle, radial or conical */
    /** 启用软件绘制复杂渐变：带角度的线性、径向或锥形 */
    #define LV_USE_DRAW_SW_COMPLEX_GRADIENTS    1

#endif

/*Use TSi's aka (Think Silicon) NemaGFX */
/* 使用 TSi（即 Think Silicon）的 NemaGFX */
#define LV_USE_NEMA_GFX 0

#if LV_USE_NEMA_GFX
    /** Select which NemaGFX HAL to use. Possible options:
     * - LV_NEMA_HAL_CUSTOM
     * - LV_NEMA_HAL_STM32 */
    /** 选择使用哪个 NemaGFX HAL。可选项：
     * - LV_NEMA_HAL_CUSTOM
     * - LV_NEMA_HAL_STM32 */
    #define LV_USE_NEMA_HAL LV_NEMA_HAL_CUSTOM
    #if LV_USE_NEMA_HAL == LV_NEMA_HAL_STM32
        #define LV_NEMA_STM32_HAL_INCLUDE <stm32u5xx_hal.h>
    #endif

    /*Enable Vector Graphics Operations. Available only if NemaVG library is present*/
    /* 启用矢量图形操作，仅在存在 NemaVG 库时可用 */
    #define LV_USE_NEMA_VG 0
    #if LV_USE_NEMA_VG
        /*Define application's resolution used for VG related buffer allocation */
        /* 定义用于 VG 相关缓冲区分配的应用程序分辨率 */
        #define LV_NEMA_GFX_MAX_RESX 800
        #define LV_NEMA_GFX_MAX_RESY 600
    #endif
#endif

/** Use NXP's VG-Lite GPU on iMX RTxxx platforms. */
    /** 在 iMX RTxxx 平台上使用 NXP 的 VG-Lite GPU。 */
#define LV_USE_DRAW_VGLITE 0

#if LV_USE_DRAW_VGLITE
    /** Enable blit quality degradation workaround recommended for screen's dimension > 352 pixels. */
    /** 启用屏幕尺寸大于 352 像素时建议的 blit 质量降级解决方案。 */
    #define LV_USE_VGLITE_BLIT_SPLIT 0

    #if LV_USE_OS
        /** Use additional draw thread for VG-Lite processing. */
        /** 为 VG-Lite 处理使用额外的绘制线程。 */
        #define LV_USE_VGLITE_DRAW_THREAD 1

        #if LV_USE_VGLITE_DRAW_THREAD
            /** Enable VGLite draw async. Queue multiple tasks and flash them once to the GPU. */
            /** 启用 VGLite 异步绘制。将多个任务排队后一次性提交到 GPU。 */
            #define LV_USE_VGLITE_DRAW_ASYNC 1
        #endif
    #endif

    /** Enable VGLite asserts. */
    /** 启用 VGLite 断言。 */
    #define LV_USE_VGLITE_ASSERT 0

    /** Enable VGLite error checks. */
    /** 启用 VGLite 错误检查。 */
    #define LV_USE_VGLITE_CHECK_ERROR 0
#endif

/** Use NXP's PXP on iMX RTxxx platforms. */
    /** 在 iMX RTxxx 平台上使用 NXP 的 PXP。 */
#define LV_USE_PXP 0

#if LV_USE_PXP
    /** Use PXP for drawing.*/
    /** 使用 PXP 进行绘制。*/
    #define LV_USE_DRAW_PXP 1

    /** Use PXP to rotate display.*/
    /** 使用 PXP 旋转显示。*/
    #define LV_USE_ROTATE_PXP 0

    #if LV_USE_DRAW_PXP && LV_USE_OS
        /** Use additional draw thread for PXP processing.*/
        /** 为 PXP 处理使用额外的绘制线程。*/
        #define LV_USE_PXP_DRAW_THREAD 1
    #endif

    /** Enable PXP asserts. */
    /** 启用 PXP 断言。 */
    #define LV_USE_PXP_ASSERT 0
#endif

/** Use NXP's G2D on MPU platforms. */
    /** 在 MPU 平台上使用 NXP 的 G2D。 */
#define LV_USE_DRAW_G2D 0

#if LV_USE_DRAW_G2D
    /** Maximum number of buffers that can be stored for G2D draw unit.
     *  Includes the frame buffers and assets. */
    /** G2D 绘制单元可存储的最大缓冲区数量。
     *  包括帧缓冲区和资源。 */
    #define LV_G2D_HASH_TABLE_SIZE 50

    #if LV_USE_OS
        /** Use additional draw thread for G2D processing.*/
        /** 为 G2D 处理使用额外的绘制线程。*/
        #define LV_USE_G2D_DRAW_THREAD 1
    #endif

    /** Enable G2D asserts. */
    /** 启用 G2D 断言。 */
    #define LV_USE_G2D_ASSERT 0
#endif

/** Use Renesas Dave2D on RA  platforms. */
/** 在 RA 平台上使用 Renesas Dave2D。 */
#define LV_USE_DRAW_DAVE2D 0

/** Draw using cached SDL textures*/
/** 使用缓存的 SDL 纹理进行绘制 */
#define LV_USE_DRAW_SDL 0

/** Use VG-Lite GPU. */
/** 使用 VG-Lite GPU。 */
#define LV_USE_DRAW_VG_LITE 0

#if LV_USE_DRAW_VG_LITE
    /** Enable VG-Lite custom external 'gpu_init()' function */
    /** 启用 VG-Lite 自定义外部 'gpu_init()' 函数 */
    #define LV_VG_LITE_USE_GPU_INIT 0

    /** Enable VG-Lite assert. */
    /** 启用 VG-Lite 断言。 */
    #define LV_VG_LITE_USE_ASSERT 0

    /** VG-Lite flush commit trigger threshold. GPU will try to batch these many draw tasks. */
    /** VG-Lite 刷新提交触发阈值。GPU 将尝试批量处理这些绘制任务。 */
    #define LV_VG_LITE_FLUSH_MAX_COUNT 8

    /** Enable border to simulate shadow.
     *  NOTE: which usually improves performance,
     *  but does not guarantee the same rendering quality as the software. */
    /** 启用边框以模拟阴影。
     *  注意：这通常会提高性能，
     *  但不能保证与软件相同的渲染质量。 */
    #define LV_VG_LITE_USE_BOX_SHADOW 1

    /** VG-Lite gradient maximum cache number.
     *  @note  The memory usage of a single gradient image is 4K bytes. */
    /** VG-Lite 渐变最大缓存数量。
     *  注意：单个渐变图像的内存使用量为 4K 字节。 */
    #define LV_VG_LITE_GRAD_CACHE_CNT 32

    /** VG-Lite stroke maximum cache number. */
    /** VG-Lite 描边最大缓存数量。 */
    #define LV_VG_LITE_STROKE_CACHE_CNT 32
#endif

/** Accelerate blends, fills, etc. with STM32 DMA2D */
/** 使用 STM32 DMA2D 加速混合、填充等操作 */
#define LV_USE_DRAW_DMA2D 0

#if LV_USE_DRAW_DMA2D
    #define LV_DRAW_DMA2D_HAL_INCLUDE "stm32h7xx_hal.h"

    /* if enabled, the user is required to call `lv_draw_dma2d_transfer_complete_interrupt_handler`
     * upon receiving the DMA2D global interrupt
     */
    /* 如果启用，用户需要在收到 DMA2D 全局中断时调用 `lv_draw_dma2d_transfer_complete_interrupt_handler` */
    #define LV_USE_DRAW_DMA2D_INTERRUPT 0
#endif

/** Draw using cached OpenGLES textures */
/** 使用缓存的 OpenGLES 纹理进行绘制 */
#define LV_USE_DRAW_OPENGLES 0

/** Draw using espressif PPA accelerator */
/** 使用乐鑫 PPA 加速器进行绘制 */
#define LV_USE_PPA  0
#if LV_USE_PPA
    #define LV_USE_PPA_IMG 0
#endif
/*=======================
 * FEATURE CONFIGURATION
 *=======================*/
/*=======================
 * 功能配置
 *=======================*/

/*-------------
 * Logging
 *-----------*/
/*-------------
 * 日志
 *-----------*/

/** Enable log module */
/** 启用日志模块 */
#define LV_USE_LOG 1
#if LV_USE_LOG
    /** Set value to one of the following levels of logging detail:
     *  - LV_LOG_LEVEL_TRACE    Log detailed information.
     *  - LV_LOG_LEVEL_INFO     Log important events.
     *  - LV_LOG_LEVEL_WARN     Log if something unwanted happened but didn't cause a problem.
     *  - LV_LOG_LEVEL_ERROR    Log only critical issues, when system may fail.
     *  - LV_LOG_LEVEL_USER     Log only custom log messages added by the user.
     *  - LV_LOG_LEVEL_NONE     Do not log anything. */
    /** 设置日志详细信息的级别：
     *  - LV_LOG_LEVEL_TRACE    记录详细信息。
     *  - LV_LOG_LEVEL_INFO     记录重要事件。
     *  - LV_LOG_LEVEL_WARN     记录发生不希望但未引起问题的情况。
     *  - LV_LOG_LEVEL_ERROR    仅记录关键问题，系统可能失败时。
     *  - LV_LOG_LEVEL_USER     仅记录用户添加的自定义日志消息。
     *  - LV_LOG_LEVEL_NONE     不记录任何内容。 */
    #define LV_LOG_LEVEL LV_LOG_LEVEL_WARN

    /** - 1: Print log with 'printf';
     *  - 0: User needs to register a callback with `lv_log_register_print_cb()`. */
    /** - 1: 使用 'printf' 打印日志；
     *  - 0: 用户需要通过 `lv_log_register_print_cb()` 注册回调。 */
    #define LV_LOG_PRINTF 1

    /** Set callback to print logs.
     *  E.g `my_print`. The prototype should be `void my_print(lv_log_level_t level, const char * buf)`.
     *  Can be overwritten by `lv_log_register_print_cb`. */
    /** 设置用于打印日志的回调函数。
     *  例如 `my_print`。原型应为 `void my_print(lv_log_level_t level, const char * buf)`。
     *  可以通过 `lv_log_register_print_cb` 覆盖。 */
    //#define LV_LOG_PRINT_CB

    /** - 1: Enable printing timestamp;
     *  - 0: Disable printing timestamp. */
    /** - 1: 启用打印时间戳；
     *  - 0: 禁用打印时间戳。 */
    #define LV_LOG_USE_TIMESTAMP 1

    /** - 1: Print file and line number of the log;
     *  - 0: Do not print file and line number of the log. */
    /** - 1: 打印日志的文件和行号；
     *  - 0: 不打印日志的文件和行号。 */
    #define LV_LOG_USE_FILE_LINE 1

    /* Enable/disable LV_LOG_TRACE in modules that produces a huge number of logs. */
    /* 启用/禁用在产生大量日志的模块中启用 LV_LOG_TRACE。 */
    #define LV_LOG_TRACE_MEM        1   /**< Enable/disable trace logs in memory operations. */
    /** 启用/禁用内存操作中的跟踪日志。 */
    #define LV_LOG_TRACE_TIMER      1   /**< Enable/disable trace logs in timer operations. */
    /** 启用/禁用定时器操作中的跟踪日志。 */
    #define LV_LOG_TRACE_INDEV      1   /**< Enable/disable trace logs in input device operations. */
    /** 启用/禁用输入设备操作中的跟踪日志。 */
    #define LV_LOG_TRACE_DISP_REFR  1   /**< Enable/disable trace logs in display re-draw operations. */
    /** 启用/禁用显示重绘操作中的跟踪日志。 */
    #define LV_LOG_TRACE_EVENT      1   /**< Enable/disable trace logs in event dispatch logic. */
    /** 启用/禁用事件分派逻辑中的跟踪日志。 */
    #define LV_LOG_TRACE_OBJ_CREATE 1   /**< Enable/disable trace logs in object creation (core `obj` creation plus every widget). */
    /** 启用/禁用对象创建（核心 `obj` 创建以及每个小部件）中的跟踪日志。 */
    #define LV_LOG_TRACE_LAYOUT     1   /**< Enable/disable trace logs in flex- and grid-layout operations. */
    /** 启用/禁用弹性布局和网格布局操作中的跟踪日志。 */
    #define LV_LOG_TRACE_ANIM       1   /**< Enable/disable trace logs in animation logic. */
    /** 启用/禁用动画逻辑中的跟踪日志。 */
    #define LV_LOG_TRACE_CACHE      1   /**< Enable/disable trace logs in cache operations. */
    /** 启用/禁用缓存操作中的跟踪日志。 */
#endif  /*LV_USE_LOG*/

/*-------------
 * Asserts
 *-----------*/
/*-------------
 * 断言
 *-----------*/

/* Enable assertion failures if an operation fails or invalid data is found.
 * If LV_USE_LOG is enabled, an error message will be printed on failure. */
/* 如果操作失败或发现无效数据，则启用断言失败。
 * 如果启用了 LV_USE_LOG，则在失败时将打印错误消息。 */
#define LV_USE_ASSERT_NULL          0   /**< Check if the parameter is NULL. (Very fast, recommended) */
/** 检查参数是否为 NULL。（非常快，推荐） */
#define LV_USE_ASSERT_MALLOC        1   /**< Checks is the memory is successfully allocated or no. (Very fast, recommended) */
/** 检查内存是否成功分配。（非常快，推荐） */
#define LV_USE_ASSERT_STYLE         0
#define LV_USE_ASSERT_MEM_INTEGRITY 0
#define LV_USE_ASSERT_OBJ           0

/** Add a custom handler when assert happens e.g. to restart MCU. */
/** 在断言发生时添加自定义处理程序，例如重启 MCU。 */
#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
#define LV_ASSERT_HANDLER while(1);     /**< Halt by default */
/** 默认停止 */

/*-------------
 * Debug
 *-----------*/
/*-------------
 * 调试
 *-----------*/

/** 1: Draw random colored rectangles over the redrawn areas. */
/** 1: 在重绘区域上绘制随机颜色的矩形。 */
#define LV_USE_REFR_DEBUG 0

/** 1: Draw a red overlay for ARGB layers and a green overlay for RGB layers*/
/** 1: 为 ARGB 层绘制红色覆盖，为 RGB 层绘制绿色覆盖 */
#define LV_USE_LAYER_DEBUG 0

/** 1: Adds the following behaviors for debugging:
 *  - Draw overlays with different colors for each draw_unit's tasks.
 *  - Draw index number of draw unit on white background.
 *  - For layers, draws index number of draw unit on black background. */
/** 1: 添加以下调试行为：
 *  - 为每个绘制单元的任务绘制不同颜色的覆盖。
 *  - 在白色背景上绘制绘制单元的索引号。
 *  - 对于图层，在黑色背景上绘制绘制单元的索引号。 */
#define LV_USE_PARALLEL_DRAW_DEBUG 0

/*-------------
 * Others
 *-----------*/
/*-------------
 * 其他
 *-----------*/

#define LV_ENABLE_GLOBAL_CUSTOM 0
#if LV_ENABLE_GLOBAL_CUSTOM
    /** Header to include for custom 'lv_global' function" */
    /** 用于自定义 'lv_global' 函数的头文件 */
    #define LV_GLOBAL_CUSTOM_INCLUDE <stdint.h>
#endif

/** Default cache size in bytes.
 *  Used by image decoders such as `lv_lodepng` to keep the decoded image in memory.
 *  If size is not set to 0, the decoder will fail to decode when the cache is full.
 *  If size is 0, the cache function is not enabled and the decoded memory will be
 *  released immediately after use. */
/** 默认缓存大小（字节）。
 *  由图像解码器（如 `lv_lodepng`）使用，用于将解码后的图像保留在内存中。
 *  如果大小未设置为 0，则当缓存已满时，解码器将无法解码。
 *  如果大小为 0，则不启用缓存功能，解码后的内存将在使用后立即释放。 */
#define LV_CACHE_DEF_SIZE       128*1024*1024

/** Default number of image header cache entries. The cache is used to store the headers of images
 *  The main logic is like `LV_CACHE_DEF_SIZE` but for image headers. */
/** 图像头缓存条目的默认数量。缓存用于存储图像头。
 *  主要逻辑类似于 `LV_CACHE_DEF_SIZE`，但针对图像头。 */
#define LV_IMAGE_HEADER_CACHE_DEF_CNT 10

/** Number of stops allowed per gradient. Increase this to allow more stops.
 *  This adds (sizeof(lv_color_t) + 1) bytes per additional stop. */
/** 每个渐变允许的停止点数量。增加此值以允许更多停止点。
 *  这将为每个附加停止点增加 (sizeof(lv_color_t) + 1) 字节。 */
#define LV_GRADIENT_MAX_STOPS   2

/** Adjust color mix functions rounding. GPUs might calculate color mix (blending) differently.
 *  - 0:   round down,
 *  - 64:  round up from x.75,
 *  - 128: round up from half,
 *  - 192: round up from x.25,
 *  - 254: round up */
/** 调整颜色混合函数的舍入。GPU 计算颜色混合（混合）可能有所不同。
 *  - 0:   向下取整，
 *  - 64:  从 x.75 向上取整，
 *  - 128: 从一半向上取整，
 *  - 192: 从 x.25 向上取整，
 *  - 254: 向上取整 */
#define LV_COLOR_MIX_ROUND_OFS  0

/** Add 2 x 32-bit variables to each `lv_obj_t` to speed up getting style properties */
/** 为每个 `lv_obj_t` 添加 2 个 32 位变量，以加快获取样式属性的速度 */
#define LV_OBJ_STYLE_CACHE      1

/** Add `id` field to `lv_obj_t` */
/** 向 `lv_obj_t` 添加 `id` 字段 */
#define LV_USE_OBJ_ID           0

/**  Enable support widget names*/
/** 启用小部件名称支持 */
#define LV_USE_OBJ_NAME         0

/** Automatically assign an ID when obj is created */
/** 创建对象时自动分配 ID */
#define LV_OBJ_ID_AUTO_ASSIGN   LV_USE_OBJ_ID

/** Use builtin obj ID handler functions:
* - lv_obj_assign_id:       Called when a widget is created. Use a separate counter for each widget class as an ID.
* - lv_obj_id_compare:      Compare the ID to decide if it matches with a requested value.
* - lv_obj_stringify_id:    Return string-ified identifier, e.g. "button3".
* - lv_obj_free_id:         Does nothing, as there is no memory allocation for the ID.
* When disabled these functions needs to be implemented by the user.*/
/** 使用内置对象 ID 处理函数：
* - lv_obj_assign_id:       在创建小部件时调用。为每个小部件类使用单独的计数器作为 ID。
* - lv_obj_id_compare:      比较 ID 以判断是否与请求值匹配。
* - lv_obj_stringify_id:    返回字符串形式的标识符，例如 "button3"。
* - lv_obj_free_id:         不执行任何操作，因为没有为 ID 分配内存。
* 禁用时，这些函数需要由用户实现。*/
#define LV_USE_OBJ_ID_BUILTIN   1

/** Use obj property set/get API. */
/** 使用对象属性设置/获取 API。 */
#define LV_USE_OBJ_PROPERTY 0

/** Enable property name support. */
/** 启用属性名称支持。 */
#define LV_USE_OBJ_PROPERTY_NAME 1

/* Use VG-Lite Simulator.
 * - Requires: LV_USE_THORVG_INTERNAL or LV_USE_THORVG_EXTERNAL */
/* 使用 VG-Lite 模拟器。
 * - 需要：LV_USE_THORVG_INTERNAL 或 LV_USE_THORVG_EXTERNAL */
#define LV_USE_VG_LITE_THORVG  0

#if LV_USE_VG_LITE_THORVG
    /** Enable LVGL's blend mode support */
    /** 启用 LVGL 的混合模式支持 */
    #define LV_VG_LITE_THORVG_LVGL_BLEND_SUPPORT 0

    /** Enable YUV color format support */
    /** 启用 YUV 颜色格式支持 */
    #define LV_VG_LITE_THORVG_YUV_SUPPORT 0

    /** Enable Linear gradient extension support */
    /** 启用线性渐变扩展支持 */
    #define LV_VG_LITE_THORVG_LINEAR_GRADIENT_EXT_SUPPORT 0

    /** Enable alignment on 16 pixels */
    /** 启用 16 像素对齐 */
    #define LV_VG_LITE_THORVG_16PIXELS_ALIGN 1

    /** Buffer address alignment */
    /** 缓冲区地址对齐 */
    #define LV_VG_LITE_THORVG_BUF_ADDR_ALIGN 64

    /** Enable multi-thread render */
    /** 启用多线程渲染 */
    #define LV_VG_LITE_THORVG_THREAD_RENDER 0
#endif

/* Enable the multi-touch gesture recognition feature */
/* 启用多点触控手势识别功能 */
/* Gesture recognition requires the use of floats */
/* 手势识别需要使用浮点数 */
#define LV_USE_GESTURE_RECOGNITION 0

/*=====================
 *  COMPILER SETTINGS
 *====================*/
/*=====================
 *  编译器设置
 *====================*/

/** For big endian systems set to 1 */
/** 对于大端系统设置为 1 */
#define LV_BIG_ENDIAN_SYSTEM 0

/** Define a custom attribute for `lv_tick_inc` function */
/** 为 `lv_tick_inc` 函数定义一个自定义属性 */
#define LV_ATTRIBUTE_TICK_INC

/** Define a custom attribute for `lv_timer_handler` function */
/** 为 `lv_timer_handler` 函数定义一个自定义属性 */
#define LV_ATTRIBUTE_TIMER_HANDLER

/** Define a custom attribute for `lv_display_flush_ready` function */
/** 为 `lv_display_flush_ready` 函数定义一个自定义属性 */
#define LV_ATTRIBUTE_FLUSH_READY

/** Align VG_LITE buffers on this number of bytes.
 *  @note  vglite_src_buf_aligned() uses this value to validate alignment of passed buffer pointers. */
/** 将 VG_LITE 缓冲区对此字节数进行对齐。
 *  注意：vglite_src_buf_aligned() 使用此值来验证传入缓冲区指针的对齐方式。 */
#define LV_ATTRIBUTE_MEM_ALIGN_SIZE 1

/** Will be added where memory needs to be aligned (with -Os data might not be aligned to boundary by default).
 *  E.g. __attribute__((aligned(4)))*/
/** 将在需要内存对齐的地方添加（使用 -Os 默认情况下数据可能不对齐到边界）。
 *  例如：__attribute__((aligned(4)))*/
#define LV_ATTRIBUTE_MEM_ALIGN

/** Attribute to mark large constant arrays, for example for font bitmaps */
/** 用于标记大型常量数组的属性，例如字体位图 */
#define LV_ATTRIBUTE_LARGE_CONST

/** Compiler prefix for a large array declaration in RAM */
/** RAM 中大型数组声明的编译器前缀 */
#define LV_ATTRIBUTE_LARGE_RAM_ARRAY

/** Place performance critical functions into a faster memory (e.g RAM) */
/** 将性能关键函数放置到更快的内存（例如 RAM）中 */
#define LV_ATTRIBUTE_FAST_MEM

/** Export integer constant to binding. This macro is used with constants in the form of LV_<CONST> that
 *  should also appear on LVGL binding API such as MicroPython. */
/** 将整数常量导出到绑定。此宏用于 LV_<CONST> 形式的常量，这些常量
 *  也应出现在 LVGL 绑定 API 中，例如 MicroPython。 */
#define LV_EXPORT_CONST_INT(int_value) struct _silence_gcc_warning  /**< The default value just prevents GCC warning */
/** 默认值仅用于防止 GCC 警告 */

/** Prefix all global extern data with this */
/** 所有全局 extern 数据都带有此前缀 */
#define LV_ATTRIBUTE_EXTERN_DATA

/** Use `float` as `lv_value_precise_t` */
/** 使用 `float` 作为 `lv_value_precise_t` */
#define LV_USE_FLOAT            1

/** Enable matrix support
 *  - Requires `LV_USE_FLOAT = 1` */
/** 启用矩阵支持
 *  - 需要 `LV_USE_FLOAT = 1` */
#define LV_USE_MATRIX           1

/** Include `lvgl_private.h` in `lvgl.h` to access internal data and functions by default */
/** 默认在 `lvgl.h` 中包含 `lvgl_private.h` 以访问内部数据和函数 */
#ifndef LV_USE_PRIVATE_API
    #define LV_USE_PRIVATE_API  0
#endif

/*==================
 *   FONT USAGE
 *===================*/
/*==================
 *   字体使用
 *===================*/

/* Montserrat fonts with ASCII range and some symbols using bpp = 4
 * https://fonts.google.com/specimen/Montserrat */
/* 带有 ASCII 范围和一些符号的 Montserrat 字体，使用 bpp = 4
 * https://fonts.google.com/specimen/Montserrat */
#define LV_FONT_MONTSERRAT_8  0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 0
#define LV_FONT_MONTSERRAT_14 0
#define LV_FONT_MONTSERRAT_16 0
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 0
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 1
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0

/* Demonstrate special features */
/* 演示特殊功能 */
#define LV_FONT_MONTSERRAT_28_COMPRESSED    1
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW    1
#define LV_FONT_SIMSUN_14_CJK               0  /**< 1000 most common CJK radicals */
/** 1000 个最常见的 CJK 部首 */
#define LV_FONT_SIMSUN_16_CJK               0  /**< 1000 most common CJK radicals */
/** 1000 个最常见的 CJK 部首 */
#define LV_FONT_SOURCE_HAN_SANS_SC_14_CJK   0  /**< 1338 most common CJK radicals */
/** 1338 个最常见的 CJK 部首 */
#define LV_FONT_SOURCE_HAN_SANS_SC_16_CJK   1

/** Pixel perfect monospaced fonts */
/** 像素完美等宽字体 */
#define LV_FONT_UNSCII_8  1
#define LV_FONT_UNSCII_16 0

/** Optionally declare custom fonts here.
 *
 *  You can use any of these fonts as the default font too and they will be available
 *  globally.  Example:
 *
 *  @code
 *  #define LV_FONT_CUSTOM_DECLARE   LV_FONT_DECLARE(my_font_1) LV_FONT_DECLARE(my_font_2)
 *  @endcode
 */
/** 在此处选择性声明自定义字体。
 *
 *  您也可以将这些字体中的任何一个用作默认字体，它们将在
 *  全局范围内可用。例如：
 *
 *  @code
 *  #define LV_FONT_CUSTOM_DECLARE   LV_FONT_DECLARE(my_font_1) LV_FONT_DECLARE(my_font_2)
 *  @endcode
 */
#define LV_FONT_CUSTOM_DECLARE

/** Always set a default font */
/** 始终设置默认字体 */
#define LV_FONT_DEFAULT &lv_font_montserrat_32

/** Enable handling large font and/or fonts with a lot of characters.
 *  The limit depends on the font size, font face and bpp.
 *  A compiler error will be triggered if a font needs it. */
/** 启用处理大字体和/或包含大量字符的字体。
 *  限制取决于字体大小、字体字形和 bpp。
 *  如果字体需要，将触发编译器错误。 */
#define LV_FONT_FMT_TXT_LARGE 1

/** Enables/disables support for compressed fonts. */
/** 启用/禁用对压缩字体的支持。 */
#define LV_USE_FONT_COMPRESSED 0

/** Enable drawing placeholders when glyph dsc is not found. */
/** 当未找到字形描述符时，启用绘制占位符。 */
#define LV_USE_FONT_PLACEHOLDER 1

/*=================
 *  TEXT SETTINGS
 *=================*/
/*=================
 *  文本设置
 *=================*/

/**
 * Select a character encoding for strings.
 * Your IDE or editor should have the same character encoding.
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 */
/**
 * 为字符串选择字符编码。
 * 您的 IDE 或编辑器应具有相同的字符编码。
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/** While rendering text strings, break (wrap) text on these chars. */
/** 在渲染文本字符串时，在这些字符上进行文本换行。 */
#define LV_TXT_BREAK_CHARS " ,.;:-_)]}"

/** If a word is at least this long, will break wherever "prettiest".
 *  To disable, set to a value <= 0. */
/** 如果一个单词至少这么长，将在“最美观”的地方换行。
 *  要禁用，请设置为 <= 0 的值。 */
#define LV_TXT_LINE_BREAK_LONG_LEN 0

/** Minimum number of characters in a long word to put on a line before a break.
 *  Depends on LV_TXT_LINE_BREAK_LONG_LEN. */
/** 长单词在换行前放在一行上的最小字符数。
 *  取决于 LV_TXT_LINE_BREAK_LONG_LEN。 */
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3

/** Minimum number of characters in a long word to put on a line after a break.
 *  Depends on LV_TXT_LINE_BREAK_LONG_LEN. */
/** 长单词在换行后放在一行上的最小字符数。
 *  取决于 LV_TXT_LINE_BREAK_LONG_LEN。 */
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3

/** Support bidirectional text. Allows mixing Left-to-Right and Right-to-Left text.
 *  The direction will be processed according to the Unicode Bidirectional Algorithm:
 *  https://www.w3.org/International/articles/inline-bidi-markup/uba-basics */
/** 支持双向文本。允许混合从左到右和从右到左的文本。
 *  方向将根据 Unicode 双向算法进行处理：
 *  https://www.w3.org/International/articles/inline-bidi-markup/uba-basics */
#define LV_USE_BIDI 0
#if LV_USE_BIDI
    /*Set the default direction. Supported values:
    *`LV_BASE_DIR_LTR` Left-to-Right
    *`LV_BASE_DIR_RTL` Right-to-Left
    *`LV_BASE_DIR_AUTO` detect text base direction*/
    /*设置默认方向。支持的值：
    *`LV_BASE_DIR_LTR` 从左到右
    *`LV_BASE_DIR_RTL` 从右到左
    *`LV_BASE_DIR_AUTO` 自动检测文本基方向*/
    #define LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_AUTO
#endif

/** Enable Arabic/Persian processing
 *  In these languages characters should be replaced with another form based on their position in the text */
/** 启用阿拉伯语/波斯语处理
 *  在这些语言中，字符应根据其在文本中的位置替换为另一种形式 */
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/*The control character to use for signaling text recoloring*/
/* 用于指示文本重新着色的控制字符 */
#define LV_TXT_COLOR_CMD "#"

/*==================
 * WIDGETS
 *================*/
/*==================
 * 小部件
 *================*/
/* Documentation for widgets can be found here: https://docs.lvgl.io/master/details/widgets/index.html . */
/* 小部件的文档可以在这里找到：https://docs.lvgl.io/master/details/widgets/index.html 。 */

/** 1: Causes these widgets to be given default values at creation time.
 *  - lv_buttonmatrix_t:  Get default maps:  {"Btn1", "Btn2", "Btn3", "\n", "Btn4", "Btn5", ""}, else map not set.
 *  - lv_checkbox_t    :  String label set to "Check box", else set to empty string.
 *  - lv_dropdown_t    :  Options set to "Option 1", "Option 2", "Option 3", else no values are set.
 *  - lv_roller_t      :  Options set to "Option 1", "Option 2", "Option 3", "Option 4", "Option 5", else no values are set.
 *  - lv_label_t       :  Text set to "Text", else empty string.
 *  - lv_arclabel_t   :  Text set to "Arced Text", else empty string.
 * */
/** 1: 使这些小部件在创建时获得默认值。
 *  - lv_buttonmatrix_t: 获取默认映射：{"Btn1", "Btn2", "Btn3", "\n", "Btn4", "Btn5", ""}, 否则不设置映射。
 *  - lv_checkbox_t    : 字符串标签设置为 "Check box", 否则设置为空字符串。
 *  - lv_dropdown_t    : 选项设置为 "Option 1", "Option 2", "Option 3", 否则不设置值。
 *  - lv_roller_t      : 选项设置为 "Option 1", "Option 2", "Option 3", "Option 4", "Option 5", 否则不设置值。
 *  - lv_label_t       : 文本设置为 "Text", 否则为空字符串。
 *  - lv_arclabel_t   : 文本设置为 "Arced Text", 否则为空字符串。
 * */
#define LV_WIDGETS_HAS_DEFAULT_VALUE  1

#define LV_USE_ANIMIMG    1

#define LV_USE_ARC        1

#define LV_USE_ARCLABEL  1

#define LV_USE_BAR        1

#define LV_USE_BUTTON        1

#define LV_USE_BUTTONMATRIX  1

#define LV_USE_CALENDAR   1
#if LV_USE_CALENDAR
    #define LV_CALENDAR_WEEK_STARTS_MONDAY 0
    #if LV_CALENDAR_WEEK_STARTS_MONDAY
        #define LV_CALENDAR_DEFAULT_DAY_NAMES {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"}
    #else
        #define LV_CALENDAR_DEFAULT_DAY_NAMES {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"}
    #endif

    #define LV_CALENDAR_DEFAULT_MONTH_NAMES {"January", "February", "March",  "April", "May",  "June", "July", "August", "September", "October", "November", "December"}
    #define LV_USE_CALENDAR_HEADER_ARROW 1
    #define LV_USE_CALENDAR_HEADER_DROPDOWN 1
    #define LV_USE_CALENDAR_CHINESE 0
#endif  /*LV_USE_CALENDAR*/

#define LV_USE_CANVAS     1

#define LV_USE_CHART      1

#define LV_USE_CHECKBOX   1

#define LV_USE_DROPDOWN   1   /**< Requires: lv_label */
/** 需要：lv_label */

#define LV_USE_IMAGE      1   /**< Requires: lv_label */
/** 需要：lv_label */

#define LV_USE_IMAGEBUTTON     1

#define LV_USE_KEYBOARD   1

#define LV_USE_LABEL      1
#if LV_USE_LABEL
    #define LV_LABEL_TEXT_SELECTION 1   /**< Enable selecting text of the label */
    /** 启用选择标签文本 */
    #define LV_LABEL_LONG_TXT_HINT 1    /**< Store some extra info in labels to speed up drawing of very long text */
    /** 在标签中存储一些额外信息以加快绘制非常长的文本 */
    #define LV_LABEL_WAIT_CHAR_COUNT 3  /**< The count of wait chart */
    /** 等待字符计数 */
#endif

#define LV_USE_LED        1

#define LV_USE_LINE       1

#define LV_USE_LIST       1

#define LV_USE_LOTTIE     0

#define LV_USE_MENU       1

#define LV_USE_MSGBOX     1

#define LV_USE_ROLLER     1   /**< Requires: lv_label */
/** 需要：lv_label */

#define LV_USE_SCALE      1

#define LV_USE_SLIDER     1   /**< Requires: lv_bar */
/** 需要：lv_bar */

#define LV_USE_SPAN       1
#if LV_USE_SPAN
    /** A line of text can contain this maximum number of span descriptors. */
    /** 一行文本可以包含的最大 span 描述符数量。 */
    #define LV_SPAN_SNIPPET_STACK_SIZE 64
#endif

#define LV_USE_SPINBOX    1

#define LV_USE_SPINNER    1

#define LV_USE_SWITCH     1

#define LV_USE_TABLE      1

#define LV_USE_TABVIEW    1

#define LV_USE_TEXTAREA   1   /**< Requires: lv_label */
/** 需要：lv_label */
#if LV_USE_TEXTAREA != 0
    #define LV_TEXTAREA_DEF_PWD_SHOW_TIME 1500    /**< [ms] */
    /** [毫秒] */
#endif

#define LV_USE_TILEVIEW   1

#define LV_USE_WIN        1

#define LV_USE_3DTEXTURE  0

/*==================
 * THEMES
 *==================*/
/*==================
 * 主题
 *==================*/
/* Documentation for themes can be found here: https://docs.lvgl.io/master/details/common-widget-features/styles/styles.html#themes . */
/* 主题的文档可以在这里找到：https://docs.lvgl.io/master/details/common-widget-features/styles/styles.html#themes 。 */

/** A simple, impressive and very complete theme */
/** 一个简单、令人印象深刻且非常完整的主题 */
#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT
    /** 0: Light mode; 1: Dark mode */
    /** 0: 亮色模式; 1: 暗色模式 */
    #define LV_THEME_DEFAULT_DARK 0

    /** 1: Enable grow on press */
    /** 1: 启用按压时放大 */
    #define LV_THEME_DEFAULT_GROW 1

    /** Default transition time in ms. */
    /** 默认过渡时间（毫秒）。 */
    #define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif /*LV_USE_THEME_DEFAULT*/

/** A very simple theme that is a good starting point for a custom theme */
/** 一个非常简单的主题，是自定义主题的良好起点 */
#define LV_USE_THEME_SIMPLE 1

/** A theme designed for monochrome displays */
/** 为单色显示器设计的主题 */
#define LV_USE_THEME_MONO 1

/*==================
 * LAYOUTS
 *==================*/
/*==================
 * 布局
 *==================*/
/* Documentation for layouts can be found here: https://docs.lvgl.io/master/details/common-widget-features/layouts/index.html . */
/* 布局的文档可以在这里找到：https://docs.lvgl.io/master/details/common-widget-features/layouts/index.html 。 */

/** A layout similar to Flexbox in CSS. */
/** 类似于 CSS 中 Flexbox 的布局。 */
#define LV_USE_FLEX 1

/** A layout similar to Grid in CSS. */
/** 类似于 CSS 中 Grid 的布局。 */
#define LV_USE_GRID 1

/*====================
 * 3RD PARTS LIBRARIES
 *====================*/
/*====================
 * 第三方库
 *====================*/
/* Documentation for libraries can be found here: https://docs.lvgl.io/master/details/libs/index.html . */
/* 库的文档可以在这里找到：https://docs.lvgl.io/master/details/libs/index.html 。 */

/* File system interfaces for common APIs */
/* 常用 API 的文件系统接口 */

/** Setting a default driver letter allows skipping the driver prefix in filepaths.
 *  Documentation about how to use the below driver-identifier letters can be found at
 *  https://docs.lvgl.io/master/details/main-modules/fs.html#lv-fs-identifier-letters . */
/** 设置默认驱动器盘符允许跳过文件路径中的驱动器前缀。
 *  有关如何使用以下驱动器标识符字母的文档可以在
 *  https://docs.lvgl.io/master/details/main-modules/fs.html#lv-fs-identifier-letters 找到。 */
#define LV_FS_DEFAULT_DRIVER_LETTER 'A'

/** API for fopen, fread, etc. */
/** 用于 fopen、fread 等的 API。 */
#define LV_USE_FS_STDIO 1
#if LV_USE_FS_STDIO
    #define LV_FS_STDIO_LETTER 'A'
    #define LV_FS_STDIO_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    /** 设置工作目录。文件/目录路径将附加到其后。 */
    #define LV_FS_STDIO_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
    /** >0 表示在 lv_fs_read() 中缓存此字节数 */
#endif

/** API for open, read, etc. */
/** 用于 open、read 等的 API。 */
#define LV_USE_FS_POSIX 0
#if LV_USE_FS_POSIX
    #define LV_FS_POSIX_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    /** 为此驱动程序设置一个大写驱动器标识符字母（例如 'A'）。 */
    #define LV_FS_POSIX_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    /** 设置工作目录。文件/目录路径将附加到其后。 */
    #define LV_FS_POSIX_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
    /** >0 表示在 lv_fs_read() 中缓存此字节数 */
#endif

/** API for CreateFile, ReadFile, etc. */
/** 用于 CreateFile、ReadFile 等的 API。 */
#define LV_USE_FS_WIN32 0
#if LV_USE_FS_WIN32
    #define LV_FS_WIN32_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    /** 为此驱动程序设置一个大写驱动器标识符字母（例如 'A'）。 */
    #define LV_FS_WIN32_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    /** 设置工作目录。文件/目录路径将附加到其后。 */
    #define LV_FS_WIN32_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
    /** >0 表示在 lv_fs_read() 中缓存此字节数 */
#endif

/** API for FATFS (needs to be added separately). Uses f_open, f_read, etc. */
/** FATFS 的 API（需要单独添加）。使用 f_open、f_read 等。 */
#define LV_USE_FS_FATFS 0
#if LV_USE_FS_FATFS
    #define LV_FS_FATFS_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    /** 为此驱动程序设置一个大写驱动器标识符字母（例如 'A'）。 */
    #define LV_FS_FATFS_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    /** 设置工作目录。文件/目录路径将附加到其后。 */
    #define LV_FS_FATFS_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
    /** >0 表示在 lv_fs_read() 中缓存此字节数 */
#endif

/** API for memory-mapped file access. */
/** 内存映射文件访问的 API。 */
#define LV_USE_FS_MEMFS 0
#if LV_USE_FS_MEMFS
    #define LV_FS_MEMFS_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    /** 为此驱动程序设置一个大写驱动器标识符字母（例如 'A'）。 */
#endif

/** API for LittleFs. */
/** LittleFs 的 API。 */
#define LV_USE_FS_LITTLEFS 0
#if LV_USE_FS_LITTLEFS
    #define LV_FS_LITTLEFS_LETTER '\0'  /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    /** 为此驱动程序设置一个大写驱动器标识符字母（例如 'A'）。 */
    #define LV_FS_LITTLEFS_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
    /** 设置工作目录。文件/目录路径将附加到其后。 */
#endif

/** API for Arduino LittleFs. */
/** Arduino LittleFs 的 API。 */
#define LV_USE_FS_ARDUINO_ESP_LITTLEFS 0
#if LV_USE_FS_ARDUINO_ESP_LITTLEFS
    #define LV_FS_ARDUINO_ESP_LITTLEFS_LETTER '\0'  /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    /** 为此驱动程序设置一个大写驱动器标识符字母（例如 'A'）。 */
    #define LV_FS_ARDUINO_ESP_LITTLEFS_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
    /** 设置工作目录。文件/目录路径将附加到其后。 */
#endif

/** API for Arduino Sd. */
/** Arduino Sd 的 API。 */
#define LV_USE_FS_ARDUINO_SD 0
#if LV_USE_FS_ARDUINO_SD
    #define LV_FS_ARDUINO_SD_LETTER '\0'  /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    /** 为此驱动程序设置一个大写驱动器标识符字母（例如 'A'）。 */
    #define LV_FS_ARDUINO_SD_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
    /** 设置工作目录。文件/目录路径将附加到其后。 */
#endif

/** API for UEFI */
/** UEFI 的 API */
#define LV_USE_FS_UEFI 0
#if LV_USE_FS_UEFI
    #define LV_FS_UEFI_LETTER '\0'      /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    /** 为此驱动程序设置一个大写驱动器标识符字母（例如 'A'）。 */
#endif

/** LODEPNG decoder library */
/** LODEPNG 解码器库 */
#define LV_USE_LODEPNG 0

/** PNG decoder(libpng) library */
/** PNG 解码器 (libpng) 库 */
#define LV_USE_LIBPNG 0

/** BMP decoder library */
/** BMP 解码器库 */
#define LV_USE_BMP 0

/** JPG + split JPG decoder library.
 *  Split JPG is a custom format optimized for embedded systems. */
/** JPG + 分割 JPG 解码器库。
 *  分割 JPG 是一种针对嵌入式系统优化的自定义格式。 */
#define LV_USE_TJPGD 0

/** libjpeg-turbo decoder library.
 *  - Supports complete JPEG specifications and high-performance JPEG decoding. */
/** libjpeg-turbo 解码器库。
 *  - 支持完整的 JPEG 规范和高性能 JPEG 解码。 */
#define LV_USE_LIBJPEG_TURBO 0

/** GIF decoder library */
/** GIF 解码器库 */
#define LV_USE_GIF 0
#if LV_USE_GIF
    /** GIF decoder accelerate */
    /** GIF 解码加速 */
    #define LV_GIF_CACHE_DECODE_DATA 0
#endif


/** Decode bin images to RAM */
/** 将 bin 图像解码到 RAM */
#define LV_BIN_DECODER_RAM_LOAD 1

/** RLE decompress library */
/** RLE 解压库 */
#define LV_USE_RLE 1

/** QR code library */
/** 二维码库 */
#define LV_USE_QRCODE 1

/** Barcode code library */
/** 条形码库 */
#define LV_USE_BARCODE 1

/** FreeType library */
/** FreeType 库 */
#define LV_USE_FREETYPE 1
#if LV_USE_FREETYPE
    /** Let FreeType use LVGL memory and file porting */
    /** 让 FreeType 使用 LVGL 内存和文件移植 */
    #define LV_FREETYPE_USE_LVGL_PORT 0

    /** Cache count of glyphs in FreeType, i.e. number of glyphs that can be cached.
     *  The higher the value, the more memory will be used. */
    /** FreeType 中字形缓存的数量，即可以缓存的字形数量。
     *  值越高，使用的内存越多。 */
    #define LV_FREETYPE_CACHE_FT_GLYPH_CNT 1024
#endif

/** Built-in TTF decoder */
/** 内置 TTF 解码器 */
#define LV_USE_TINY_TTF 0
#if LV_USE_TINY_TTF
    /* Enable loading TTF data from files */
    /* 启用从文件加载 TTF 数据 */
    #define LV_TINY_TTF_FILE_SUPPORT 0
    #define LV_TINY_TTF_CACHE_GLYPH_CNT 128
    #define LV_TINY_TTF_CACHE_KERNING_CNT 256
#endif

/** Rlottie library */
/** Rlottie 库 */
#define LV_USE_RLOTTIE 0

/** Enable Vector Graphic APIs
 *  - Requires `LV_USE_MATRIX = 1` */
/** 启用矢量图形 API
 *  - 需要 `LV_USE_MATRIX = 1` */
#define LV_USE_VECTOR_GRAPHIC  0

/** Enable ThorVG (vector graphics library) from the src/libs folder */
/** 从 src/libs 文件夹启用 ThorVG（矢量图形库） */
#define LV_USE_THORVG_INTERNAL 0

/** Enable ThorVG by assuming that its installed and linked to the project */
/** 通过假设 ThorVG 已安装并链接到项目来启用 ThorVG */
#define LV_USE_THORVG_EXTERNAL 0

/** Use lvgl built-in LZ4 lib */
/** 使用 lvgl 内置的 LZ4 库 */
#define LV_USE_LZ4_INTERNAL  0

/** Use external LZ4 library */
/** 使用外部 LZ4 库 */
#define LV_USE_LZ4_EXTERNAL  0

/*SVG library
 *  - Requires `LV_USE_VECTOR_GRAPHIC = 1` */
/* SVG 库
 *  - 需要 `LV_USE_VECTOR_GRAPHIC = 1` */
#define LV_USE_SVG 0
#define LV_USE_SVG_ANIMATION 0
#define LV_USE_SVG_DEBUG 0

/** FFmpeg library for image decoding and playing videos.
 *  Supports all major image formats so do not enable other image decoder with it. */
/** 用于图像解码和视频播放的 FFmpeg 库。
 *  支持所有主要图像格式，因此不要同时启用其他图像解码器。 */
#define LV_USE_FFMPEG 1
#if LV_USE_FFMPEG
    /** Dump input information to stderr */
    /** 将输入信息转储到 stderr */
    #define LV_FFMPEG_DUMP_FORMAT 0
    /** Use lvgl file path in FFmpeg Player widget
     *  You won't be able to open URLs after enabling this feature.
     *  Note that FFmpeg image decoder will always use lvgl file system. */
    /** 在 FFmpeg 播放器小部件中使用 lvgl 文件路径
     *  启用此功能后，您将无法打开 URL。
     *  请注意，FFmpeg 图像解码器将始终使用 lvgl 文件系统。 */
    #define LV_FFMPEG_PLAYER_USE_LV_FS 0
#endif

/*==================
 * OTHERS
 *==================*/
/*==================
 * 其他
 *==================*/
/* Documentation for several of the below items can be found here: https://docs.lvgl.io/master/details/auxiliary-modules/index.html . */
/* 以下各项的文档可以在这里找到：https://docs.lvgl.io/master/details/auxiliary-modules/index.html 。 */

/** 1: Enable API to take snapshot for object */
/** 1: 启用 API 以获取对象的快照 */
#define LV_USE_SNAPSHOT 0

/** 1: Enable system monitor component */
/** 1: 启用系统监视器组件 */
#define LV_USE_SYSMON   1
#if LV_USE_SYSMON
    /** Get the idle percentage. E.g. uint32_t my_get_idle(void); */
    /** 获取空闲百分比。例如 uint32_t my_get_idle(void); */
    #define LV_SYSMON_GET_IDLE lv_os_get_idle_percent
    /** 1: Enable usage of lv_os_get_proc_idle_percent.*/
    /** 1: 启用 lv_os_get_proc_idle_percent 的使用。*/
    #define LV_SYSMON_PROC_IDLE_AVAILABLE 0
    #if LV_SYSMON_PROC_IDLE_AVAILABLE
        /** Get the applications idle percentage.
         * - Requires `LV_USE_OS == LV_OS_PTHREAD` */
        /** 获取应用程序空闲百分比。
         * - 需要 `LV_USE_OS == LV_OS_PTHREAD` */
        #define LV_SYSMON_GET_PROC_IDLE lv_os_get_proc_idle_percent
    #endif 

    /** 1: Show CPU usage and FPS count.
     *  - Requires `LV_USE_SYSMON = 1` */
    /** 1: 显示 CPU 使用率和 FPS 计数。
     *  - 需要 `LV_USE_SYSMON = 1` */
    //显示fps,右下角!
    #define LV_USE_PERF_MONITOR 0
    #if LV_USE_PERF_MONITOR
        #define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT

        /** 0: Displays performance data on the screen; 1: Prints performance data using log. */
        /** 0: 在屏幕上显示性能数据；1: 使用日志打印性能数据。 */
        #define LV_USE_PERF_MONITOR_LOG_MODE 0
    #endif

    /** 1: Show used memory and memory fragmentation.
     *     - Requires `LV_USE_STDLIB_MALLOC = LV_STDLIB_BUILTIN`
     *     - Requires `LV_USE_SYSMON = 1`*/
    /** 1: 显示已用内存和内存碎片。
     *     - 需要 `LV_USE_STDLIB_MALLOC = LV_STDLIB_BUILTIN`
     *     - 需要 `LV_USE_SYSMON = 1`*/
    #define LV_USE_MEM_MONITOR 0
    #if LV_USE_MEM_MONITOR
        #define LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_LEFT
    #endif
#endif /*LV_USE_SYSMON*/

/** 1: Enable runtime performance profiler */
/** 1: 启用运行时性能分析器 */
#define LV_USE_PROFILER 0
#if LV_USE_PROFILER
    /** 1: Enable the built-in profiler */
    /** 1: 启用内置分析器 */
    #define LV_USE_PROFILER_BUILTIN 1
    #if LV_USE_PROFILER_BUILTIN
        /** Default profiler trace buffer size */
        /** 默认分析器跟踪缓冲区大小 */
        #define LV_PROFILER_BUILTIN_BUF_SIZE (16 * 1024)     /**< [bytes] */
        /** [字节] */
        #define LV_PROFILER_BUILTIN_DEFAULT_ENABLE 1
    #endif

    /** Header to include for profiler */
    /** 用于分析器的头文件 */
    #define LV_PROFILER_INCLUDE "lvgl/src/misc/lv_profiler_builtin.h"

    /** Profiler start point function */
    /** 分析器起始点函数 */
    #define LV_PROFILER_BEGIN    LV_PROFILER_BUILTIN_BEGIN

    /** Profiler end point function */
    /** 分析器结束点函数 */
    #define LV_PROFILER_END      LV_PROFILER_BUILTIN_END

    /** Profiler start point function with custom tag */
    /** 带有自定义标签的分析器起始点函数 */
    #define LV_PROFILER_BEGIN_TAG LV_PROFILER_BUILTIN_BEGIN_TAG

    /** Profiler end point function with custom tag */
    /** 带有自定义标签的分析器结束点函数 */
    #define LV_PROFILER_END_TAG   LV_PROFILER_BUILTIN_END_TAG

    /*Enable layout profiler*/
    /* 启用布局分析器 */
    #define LV_PROFILER_LAYOUT 1

    /*Enable disp refr profiler*/
    /* 启用显示刷新分析器 */
    #define LV_PROFILER_REFR 1

    /*Enable draw profiler*/
    /* 启用绘制分析器 */
    #define LV_PROFILER_DRAW 1

    /*Enable indev profiler*/
    /* 启用输入设备分析器 */
    #define LV_PROFILER_INDEV 1

    /*Enable decoder profiler*/
    /* 启用解码器分析器 */
    #define LV_PROFILER_DECODER 1

    /*Enable font profiler*/
    /* 启用字体分析器 */
    #define LV_PROFILER_FONT 1

    /*Enable fs profiler*/
    /* 启用文件系统分析器 */
    #define LV_PROFILER_FS 1

    /*Enable style profiler*/
    /* 启用样式分析器 */
    #define LV_PROFILER_STYLE 0

    /*Enable timer profiler*/
    /* 启用定时器分析器 */
    #define LV_PROFILER_TIMER 1

    /*Enable cache profiler*/
    /* 启用缓存分析器 */
    #define LV_PROFILER_CACHE 1

    /*Enable event profiler*/
    /* 启用事件分析器 */
    #define LV_PROFILER_EVENT 1
#endif

/** 1: Enable Monkey test */
/** 1: 启用 Monkey 测试 */
#define LV_USE_MONKEY 0

/** 1: Enable grid navigation */
/** 1: 启用网格导航 */
#define LV_USE_GRIDNAV 0

/** 1: Enable `lv_obj` fragment logic */
/** 1: 启用 `lv_obj` 片段逻辑 */
#define LV_USE_FRAGMENT 0

/** 1: Support using images as font in label or span widgets */
/** 1: 支持在标签或 span 小部件中使用图像作为字体 */
#define LV_USE_IMGFONT 1

/** 1: Enable an observer pattern implementation */
/** 1: 启用观察者模式实现 */
#define LV_USE_OBSERVER 1

/** 1: Enable Pinyin input method
 *  - Requires: lv_keyboard */
/** 1: 启用拼音输入法
 *  - 需要：lv_keyboard */
#define LV_USE_IME_PINYIN 0
#if LV_USE_IME_PINYIN
    /** 1: Use default thesaurus.
     *  @note  If you do not use the default thesaurus, be sure to use `lv_ime_pinyin` after setting the thesaurus. */
    /** 1: 使用默认词库。
     *  注意：如果您不使用默认词库，请务必在设置词库后使用 `lv_ime_pinyin`。 */
    #define LV_IME_PINYIN_USE_DEFAULT_DICT 1
    /** Set maximum number of candidate panels that can be displayed.
     *  @note  This needs to be adjusted according to size of screen. */
    /** 设置可显示的最大候选面板数量。
     *  注意：这需要根据屏幕尺寸进行调整。 */
    #define LV_IME_PINYIN_CAND_TEXT_NUM 6

    /** Use 9-key input (k9). */
    /** 使用 9 键输入 (k9)。 */
    #define LV_IME_PINYIN_USE_K9_MODE      1
    #if LV_IME_PINYIN_USE_K9_MODE == 1
        #define LV_IME_PINYIN_K9_CAND_TEXT_NUM 3
    #endif /*LV_IME_PINYIN_USE_K9_MODE*/
#endif

/** 1: Enable file explorer.
 *  - Requires: lv_table */
/** 1: 启用文件浏览器。
 *  - 需要：lv_table */
#define LV_USE_FILE_EXPLORER                     1
#if LV_USE_FILE_EXPLORER
    /** Maximum length of path */
    /** 路径的最大长度 */
    #define LV_FILE_EXPLORER_PATH_MAX_LEN        (1024)
    /** Quick access bar, 1:use, 0:do not use.
     *  - Requires: lv_list */
    /** 快速访问栏，1:使用，0:不使用。
     *  - 需要：lv_list */
    #define LV_FILE_EXPLORER_QUICK_ACCESS        1
#endif

/** 1: Enable Font manager */
/** 1: 启用字体管理器 */
#define LV_USE_FONT_MANAGER                     0
#if LV_USE_FONT_MANAGER

/**Font manager name max length*/
/** 字体管理器名称最大长度 */
#define LV_FONT_MANAGER_NAME_MAX_LEN            32

#endif

/** Enable emulated input devices, time emulation, and screenshot compares. */
/** 启用模拟输入设备、时间模拟和屏幕截图比较。 */
#define LV_USE_TEST 0
#if LV_USE_TEST

/** Enable `lv_test_screenshot_compare`.
 * Requires libpng and a few MB of extra RAM. */
/** 启用 `lv_test_screenshot_compare`。
 * 需要 libpng 和几 MB 的额外 RAM。 */
#define LV_USE_TEST_SCREENSHOT_COMPARE 0
#endif /*LV_USE_TEST*/

/** Enable loading XML UIs runtime */
/** 启用运行时加载 XML UI */
#define LV_USE_XML    0

/** 1: Enable text translation support */
/** 1: 启用文本翻译支持 */
#define LV_USE_TRANSLATION 0

/*1: Enable color filter style*/
/* 1: 启用颜色滤镜样式 */
#define LV_USE_COLOR_FILTER     0

/*==================
 * DEVICES
 *==================*/
/*==================
 * 设备
 *==================*/

/** Use SDL to open window on PC and handle mouse and keyboard. */
/** 使用 SDL 在 PC 上打开窗口并处理鼠标和键盘。 */
#define LV_USE_SDL              0
#if LV_USE_SDL
    #define LV_SDL_INCLUDE_PATH     <SDL2/SDL.h>
    #define LV_SDL_RENDER_MODE      LV_DISPLAY_RENDER_MODE_DIRECT   /**< LV_DISPLAY_RENDER_MODE_DIRECT is recommended for best performance */
    /** LV_DISPLAY_RENDER_MODE_DIRECT 推荐用于最佳性能 */
    #define LV_SDL_BUF_COUNT        1    /**< 1 or 2 */
    /** 1 或 2 */
    #define LV_SDL_ACCELERATED      1    /**< 1: Use hardware acceleration*/
    /** 1: 使用硬件加速 */
    #define LV_SDL_FULLSCREEN       0    /**< 1: Make the window full screen by default */
    /** 1: 默认使窗口全屏 */
    #define LV_SDL_DIRECT_EXIT      1    /**< 1: Exit the application when all SDL windows are closed */
    /** 1: 当所有 SDL 窗口关闭时退出应用程序 */
    #define LV_SDL_MOUSEWHEEL_MODE  LV_SDL_MOUSEWHEEL_MODE_ENCODER  /*LV_SDL_MOUSEWHEEL_MODE_ENCODER/CROWN*/
    /*LV_SDL_MOUSEWHEEL_MODE_ENCODER/CROWN*/
#endif

/** Use X11 to open window on Linux desktop and handle mouse and keyboard */
/** 使用 X11 在 Linux 桌面打开窗口并处理鼠标和键盘 */
#define LV_USE_X11              0
#if LV_USE_X11
    #define LV_X11_DIRECT_EXIT         1  /**< Exit application when all X11 windows have been closed */
    /** 当所有 X11 窗口都已关闭时退出应用程序 */
    #define LV_X11_DOUBLE_BUFFER       1  /**< Use double buffers for rendering */
    /** 使用双缓冲区进行渲染 */
    /* Select only 1 of the following render modes (LV_X11_RENDER_MODE_PARTIAL preferred!). */
    /* 仅选择以下渲染模式之一（首选 LV_X11_RENDER_MODE_PARTIAL！）。 */
    #define LV_X11_RENDER_MODE_PARTIAL 1  /**< Partial render mode (preferred) */
    /** 部分渲染模式（首选） */
    #define LV_X11_RENDER_MODE_DIRECT  0  /**< Direct render mode */
    /** 直接渲染模式 */
    #define LV_X11_RENDER_MODE_FULL    0  /**< Full render mode */
    /** 完全渲染模式 */
#endif

/** Use Wayland to open a window and handle input on Linux or BSD desktops */
/** 使用 Wayland 在 Linux 或 BSD 桌面打开窗口并处理输入 */
#define LV_USE_WAYLAND          0
#if LV_USE_WAYLAND
    #define LV_WAYLAND_BUF_COUNT            1    /**< Use 1 for single buffer with partial render mode or 2 for double buffer with full render mode*/
    /** 在部分渲染模式下使用 1 作为单缓冲区，或在完全渲染模式下使用 2 作为双缓冲区 */
    #define LV_WAYLAND_USE_DMABUF           0    /**< Use DMA buffers for frame buffers. Requires LV_DRAW_USE_G2D */
    /** 将 DMA 缓冲区用于帧缓冲区。需要 LV_DRAW_USE_G2D */
    #define LV_WAYLAND_RENDER_MODE          LV_DISPLAY_RENDER_MODE_PARTIAL   /**< DMABUF supports LV_DISPLAY_RENDER_MODE_FULL and LV_DISPLAY_RENDER_MODE_DIRECT*/
    /** DMABUF 支持 LV_DISPLAY_RENDER_MODE_FULL 和 LV_DISPLAY_RENDER_MODE_DIRECT */
                                                                             /**< When LV_WAYLAND_USE_DMABUF is disabled, only LV_DISPLAY_RENDER_MODE_PARTIAL is supported*/
    /** 当 LV_WAYLAND_USE_DMABUF 禁用时，仅支持 LV_DISPLAY_RENDER_MODE_PARTIAL */
    #define LV_WAYLAND_WINDOW_DECORATIONS   0    /**< Draw client side window decorations only necessary on Mutter/GNOME. Not supported using DMABUF*/
    /** 仅在 Mutter/GNOME 上才需要绘制客户端窗口装饰。使用 DMABUF 不支持 */
    #define LV_WAYLAND_WL_SHELL             0    /**< Use the legacy wl_shell protocol instead of the default XDG shell*/
    /** 使用旧版 wl_shell 协议而不是默认的 XDG shell */
#endif

/** Driver for /dev/fb */
/** /dev/fb 的驱动程序 */
#define LV_USE_LINUX_FBDEV      1
#if LV_USE_LINUX_FBDEV
    #define LV_LINUX_FBDEV_BSD           0
    // #define LV_LINUX_FBDEV_RENDER_MODE   LV_DISPLAY_RENDER_MODE_FULL
    // #define LV_LINUX_FBDEV_RENDER_MODE   LV_DISPLAY_RENDER_MODE_DIRECT
    #define LV_LINUX_FBDEV_RENDER_MODE   LV_DISPLAY_RENDER_MODE_PARTIAL
    #define LV_LINUX_FBDEV_BUFFER_COUNT  2
    #define LV_LINUX_FBDEV_BUFFER_SIZE   2560*1440*2*2
    #define LV_LINUX_FBDEV_MMAP          1
#endif

/** Use Nuttx to open window and handle touchscreen */
/** 使用 Nuttx 打开窗口并处理触摸屏 */
#define LV_USE_NUTTX    0

#if LV_USE_NUTTX
    #define LV_USE_NUTTX_INDEPENDENT_IMAGE_HEAP 0

    /** Use independent image heap for default draw buffer */
    /** 对默认绘图缓冲区使用独立的图像堆 */
    #define LV_NUTTX_DEFAULT_DRAW_BUF_USE_INDEPENDENT_IMAGE_HEAP    0

    #define LV_USE_NUTTX_LIBUV    0

    /** Use Nuttx custom init API to open window and handle touchscreen */
    /** 使用 Nuttx 自定义初始化 API 打开窗口并处理触摸屏 */
    #define LV_USE_NUTTX_CUSTOM_INIT    0

    /** Driver for /dev/lcd */
    /** /dev/lcd 的驱动程序 */
    #define LV_USE_NUTTX_LCD      0
    #if LV_USE_NUTTX_LCD
        #define LV_NUTTX_LCD_BUFFER_COUNT    0
        #define LV_NUTTX_LCD_BUFFER_SIZE     60
    #endif

    /** Driver for /dev/input */
    /** /dev/input 的驱动程序 */
    #define LV_USE_NUTTX_TOUCHSCREEN    0

    /** Touchscreen cursor size in pixels(<=0: disable cursor) */
    /** 触摸屏光标大小（像素）（<=0：禁用光标） */
    #define LV_NUTTX_TOUCHSCREEN_CURSOR_SIZE    0

    /** Driver for /dev/mouse */
    /** /dev/mouse 的驱动程序 */
    #define LV_USE_NUTTX_MOUSE    0

    /** Mouse movement step (pixels) */
    /** 鼠标移动步长（像素） */
    #define LV_USE_NUTTX_MOUSE_MOVE_STEP    1
#endif

/** Driver for /dev/dri/card */
/** /dev/dri/card 的驱动程序 */
#define LV_USE_LINUX_DRM        0

#if LV_USE_LINUX_DRM

    /* Use the MESA GBM library to allocate DMA buffers that can be
     * shared across sub-systems and libraries using the Linux DMA-BUF API.
     * The GBM library aims to provide a platform independent memory management system
     * it supports the major GPU vendors - This option requires linking with libgbm */
    /* 使用 MESA GBM 库分配 DMA 缓冲区，这些缓冲区可以使用 Linux DMA-BUF API
     * 在子系统和库之间共享。
     * GBM 库旨在提供一个平台独立的内存管理系统
     * 它支持主要的 GPU 供应商 - 此选项需要链接 libgbm */
    #define LV_USE_LINUX_DRM_GBM_BUFFERS 0
#endif

/** Interface for TFT_eSPI */
/** TFT_eSPI 的接口 */
#define LV_USE_TFT_ESPI         0

/** Driver for evdev input devices */
/** evdev 输入设备的驱动程序 */
#define LV_USE_EVDEV    1

/** Driver for libinput input devices */
/** libinput 输入设备的驱动程序 */
#define LV_USE_LIBINPUT    0

#if LV_USE_LIBINPUT
    #define LV_LIBINPUT_BSD    0

    /** Full keyboard support */
    /** 完整的键盘支持 */
    #define LV_LIBINPUT_XKB             0
    #if LV_LIBINPUT_XKB
        /** "setxkbmap -query" can help find the right values for your keyboard */
        /** "setxkbmap -query" 可以帮助您为键盘找到正确的值 */
        #define LV_LIBINPUT_XKB_KEY_MAP { .rules = NULL, .model = "pc101", .layout = "us", .variant = NULL, .options = NULL }
    #endif
#endif

/* Drivers for LCD devices connected via SPI/parallel port */
/* 通过 SPI/并行端口连接的 LCD 设备的驱动程序 */
#define LV_USE_ST7735        0
#define LV_USE_ST7789        0
#define LV_USE_ST7796        0
#define LV_USE_ILI9341       0
#define LV_USE_FT81X         0

#if (LV_USE_ST7735 | LV_USE_ST7789 | LV_USE_ST7796 | LV_USE_ILI9341)
    #define LV_USE_GENERIC_MIPI 1
#else
    #define LV_USE_GENERIC_MIPI 0
#endif

/** Driver for Renesas GLCD */
/** Renesas GLCD 的驱动程序 */
#define LV_USE_RENESAS_GLCDC    0

/** Driver for ST LTDC */
/** ST LTDC 的驱动程序 */
#define LV_USE_ST_LTDC    0
#if LV_USE_ST_LTDC
    /* Only used for partial. */
    /* 仅用于部分。 */
    #define LV_ST_LTDC_USE_DMA2D_FLUSH 0
#endif

/** Driver for NXP ELCDIF */
/** NXP ELCDIF 的驱动程序 */
#define LV_USE_NXP_ELCDIF   0

/** LVGL Windows backend */
/** LVGL Windows 后端 */
#define LV_USE_WINDOWS    0

/** LVGL UEFI backend */
/** LVGL UEFI 后端 */
#define LV_USE_UEFI 0
#if LV_USE_UEFI
    #define LV_USE_UEFI_INCLUDE "myefi.h"   /**< Header that hides the actual framework (EDK2, gnu-efi, ...) */
    /** 隐藏实际框架（EDK2、gnu-efi 等）的头文件 */
    #define LV_UEFI_USE_MEMORY_SERVICES 0   /**< Use the memory functions from the boot services table */
    /** 使用引导服务表中的内存函数 */
#endif

/** Use OpenGL to open window on PC and handle mouse and keyboard */
/** 使用 OpenGL 在 PC 上打开窗口并处理鼠标和键盘 */
#define LV_USE_OPENGLES   0
#if LV_USE_OPENGLES
    #define LV_USE_OPENGLES_DEBUG        1    /**< Enable or disable debug for opengles */
    /** 启用或禁用 opengles 调试 */
#endif

/** QNX Screen display and input drivers */
/** QNX 屏幕显示和输入驱动程序 */
#define LV_USE_QNX              0
#if LV_USE_QNX
    #define LV_QNX_BUF_COUNT        1    /**< 1 or 2 */
    /** 1 或 2 */
#endif

/*=====================
* BUILD OPTIONS
*======================*/
/*=====================
* 构建选项
*======================*/

/** Enable examples to be built with the library. */
/** 允许库构建示例。 */
#define LV_BUILD_EXAMPLES 0

/** Build the demos */
/** 构建演示 */
#define LV_BUILD_DEMOS 1

/*===================
 * DEMO USAGE
 ====================*/
/*===================
 * 演示使用
 ====================*/

#if LV_BUILD_DEMOS
    /** Show some widgets. This might be required to increase `LV_MEM_SIZE`. */
    /** 显示一些小部件。这可能需要增加 `LV_MEM_SIZE`。 */
    #define LV_USE_DEMO_WIDGETS 1

    /** Demonstrate usage of encoder and keyboard. */
    /** 演示编码器和键盘的使用。 */
    #define LV_USE_DEMO_KEYPAD_AND_ENCODER 0

    /** Benchmark your system */
    /** 对您的系统进行基准测试 */
    #define LV_USE_DEMO_BENCHMARK 0

    #if LV_USE_DEMO_BENCHMARK
        /** Use fonts where bitmaps are aligned 16 byte and has Nx16 byte stride */
        /** 使用位图对齐 16 字节且具有 Nx16 字节步幅的字体 */
        #define LV_DEMO_BENCHMARK_ALIGNED_FONTS 0
    #endif

    /** Render test for each primitive.
     *  - Requires at least 480x272 display. */
    /** 每个图元的渲染测试。
     *  - 需要至少 480x272 的显示器。 */
    #define LV_USE_DEMO_RENDER 0

    /** Stress test for LVGL */
    /** LVGL 的压力测试 */
    #define LV_USE_DEMO_STRESS 0

    /** Music player demo */
    /** 音乐播放器演示 */
    #define LV_USE_DEMO_MUSIC 0
    #if LV_USE_DEMO_MUSIC
        #define LV_DEMO_MUSIC_SQUARE    0
        #define LV_DEMO_MUSIC_LANDSCAPE 0
        #define LV_DEMO_MUSIC_ROUND     0
        #define LV_DEMO_MUSIC_LARGE     0
        #define LV_DEMO_MUSIC_AUTO_PLAY 0
    #endif

    /** Vector graphic demo */
    /** 矢量图形演示 */
    #define LV_USE_DEMO_VECTOR_GRAPHIC  0

    /*---------------------------
     * Demos from lvgl/lv_demos
      ---------------------------*/
    /*---------------------------
     * 来自 lvgl/lv_demos 的演示
      ---------------------------*/

    /** Flex layout demo */
    /** Flex 布局演示 */
    #define LV_USE_DEMO_FLEX_LAYOUT     0

    /** Smart-phone like multi-language demo */
    /** 智能手机式多语言演示 */
    #define LV_USE_DEMO_MULTILANG       0

    /** Widget transformation demo */
    /** 小部件变换演示 */
    #define LV_USE_DEMO_TRANSFORM       0

    /** Demonstrate scroll settings */
    /** 演示滚动设置 */
    #define LV_USE_DEMO_SCROLL          0

    /*E-bike demo with Lottie animations (if LV_USE_LOTTIE is enabled)*/
    /* 带 Lottie 动画的电动自行车演示（如果 LV_USE_LOTTIE 已启用） */
    #define LV_USE_DEMO_EBIKE           0
    #if LV_USE_DEMO_EBIKE
        #define LV_DEMO_EBIKE_PORTRAIT  0    /*0: for 480x270..480x320, 1: for 480x800..720x1280*/
        /*0: 适用于 480x270..480x320，1: 适用于 480x800..720x1280*/
    #endif

    /** High-resolution demo */
    /** 高分辨率演示 */
    #define LV_USE_DEMO_HIGH_RES        0

    /* Smart watch demo */
    /* 智能手表演示 */
    #define LV_USE_DEMO_SMARTWATCH      0
#endif /* LV_BUILD_DEMOS */

/*--END OF LV_CONF_H--*/
/*--LV_CONF_H 结束--*/

#endif /*LV_CONF_H*/

#endif /*End of "Content enable"*/
