###########################################################
# GCC template makefile
###########################################################

ifeq ($(CONFIG_CMSIS_SAMPLE_HELLO_WORLD_Z1), y)

    SUB_ARCH := 
    SUB_ARCH += 01.Z1.Src001.HelloWorld/Src

    SUB_ARCH := $(addprefix $(TOP)/SampleChapter/StudyCode/MStory2.0/MANGO-Z1/, $(SUB_ARCH))

    vpath %.c $(SUB_ARCH)
    vpath %.s $(SUB_ARCH)

    sinclude $(addsuffix /Makefile.inc, $(SUB_ARCH))

else ifeq ($(CONFIG_CMSIS_LED_KEY_CONTROL), y)

    SUB_ARCH :=
    SUB_ARCH += 02.Z1.Src002.LedKeyControl/Src

    SUB_ARCH := $(addprefix $(TOP)/SampleChapter/StudyCode/MStory2.0/MANGO-Z1/, $(SUB_ARCH))

    vpath %.c $(SUB_ARCH)
    vpath %.s $(SUB_ARCH)

    sinclude $(addsuffix /Makefile.inc, $(SUB_ARCH))

else

endif