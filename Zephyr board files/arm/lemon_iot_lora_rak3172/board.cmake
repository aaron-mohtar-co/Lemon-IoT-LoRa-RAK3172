# SPDX-License-Identifier: Apache-2.0

board_runner_args(jlink "--device=STM32WLE5CC" "--speed=4000" "--reset-after-load")
board_runner_args(stm32cubeprogrammer "--port=swd" "--reset=hw")

include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
include(${ZEPHYR_BASE}/boards/common/stm32cubeprogrammer.board.cmake)

