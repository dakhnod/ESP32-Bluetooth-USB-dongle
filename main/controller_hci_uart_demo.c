/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_bt.h"
#include "soc/uhci_periph.h"
#include "driver/uart.h"
#include "esp_private/periph_ctrl.h" // for enabling UHCI module, remove it after UHCI driver is released
#include "esp_log.h"

void app_main(void)
{
    esp_err_t ret;

    /* Initialize NVS — it is used to store PHY calibration data */
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    periph_module_enable(PERIPH_UHCI0_MODULE);

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    bt_cfg.hci_uart_no = 0;
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret != ESP_OK) {
        // ESP_LOGE(tag, "Bluetooth Controller initialize failed: %s", esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM);
    if (ret != ESP_OK) {
        // ESP_LOGE(tag, "Bluetooth Controller initialize failed: %s", esp_err_to_name(ret));
        return;
    }
}
