# 1.编译时lvgl_helpers.c报错代码，注释掉

// assert((0 <= host) && (SPI_HOST_MAX > host));

    // const char *spi_names[] = {

    //     "SPI1_HOST", "SPI2_HOST", "SPI3_HOST"

    // };

第一次修改为,pic目录下code1.png图片所示依然报错

第二次修改为如下代码，编译通过，本次工程先这样使用。和原来代码的区别在于ESP32-IDF部分宏定义已经改变，不同芯片定义不同

assert((SPI_HOST <= host) && (VSPI_HOST >= host));

    const char *spi_names[] = {

        "SPI_HOST", "HSPI_HOST", "VSPI_HOST"

    };

    dma_channel = SPI_DMA_CH_AUTO;//DMA通道自动选择

# 2.编译时提示以下两个宏未定义，下面的代码是手动在lvgl_helpers.h中定义，然后编译通过

#define LV_HOR_RES_MAX 128

#define LV_VER_RES_MAX 64

# 3.在components/porting/下增加3个文件 CMakeLists.txt lv_port_disp.c lv_port_disp.h（修改项目比较多）链接中的视频13分钟开始

修改参考https://www.bilibili.com/video/BV1ie4y1h7eD/?spm_id_from=333.999.0.0&vd_source=302be7e2265cdca9d825cf81f3ef0821

# 4.在\lvgl\env_support\cmake\esp.cmake 中增加如下代码，用以包含demo.h。第二行为增加部分

1 file(GLOB_RECURSE SOURCES ${LVGL_ROOT_DIR}/src/*.c
                          
2                           ${LVGL_ROOT_DIR}/demos/*.c)

在14行后插入    ${LVGL_ROOT_DIR}/demos

在28后增加demos路径 ${LVGL_ROOT_DIR}/src ${LVGL_ROOT_DIR}/../ ${LVGL_ROOT_DIR}/demos)

