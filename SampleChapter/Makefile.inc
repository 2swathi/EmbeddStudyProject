###########################################################
# GCC template makefile
###########################################################


SUB_ARCH := 
SUB_ARCH += StudyCode
SUB_ARCH += FreeRTOS_StudyCode


SUB_ARCH := $(addprefix $(TOP)/SampleChapter/, $(SUB_ARCH))

vpath %.c $(SUB_ARCH)
vpath %.s $(SUB_ARCH)

sinclude $(addsuffix /Makefile.inc, $(SUB_ARCH))