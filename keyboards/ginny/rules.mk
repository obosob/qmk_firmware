# MCU name
MCU = atmega32u4
BOOTLOADER = atmel-dfu

CUSTOM_MATRIX			= yes
DEBUG_ENABLE			= no
STENO_ENABLE			= no
VIRTSER_ENABLE		= no
NKRO_ENABLE				= yes

DEBOUNCE_TYPE			= eager_pr

# Lets try and save some space eh?
MOUSEKEY_ENABLE   = no
EXTRAKEY_ENABLE   = no
CONSOLE_ENABLE    = no
COMMAND_ENABLE    = no
BOOTMAGIC_ENABLE  = no
SPACE_CADET_ENABLE  = no
MAGIC_ENABLE = no

SRC							+= matrix.c
QUANTUM_LIB_SRC += i2c_master.c
OPT_DEFS				+= -DONLYQWERTY
LTO_ENABLE = yes
