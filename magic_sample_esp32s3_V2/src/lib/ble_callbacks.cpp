#include <NimBLEServer.h>

#include "Arduino.h"
#include "ble_callbacks.h"

#if defined(CONFIG_ARDUHAL_ESP_LOG)
  #include "esp32-hal-log.h"
  #define LOG_TAG ""
#else
  #include "esp_log.h"
  static const char* LOG_TAG = "NimBLEDevice";
#endif


/* ====================================================================================================================== */
/** Characteristic コールバック クラス */
/* ====================================================================================================================== */

CharacteristicCallbacks::CharacteristicCallbacks(void) {
};

void CharacteristicCallbacks::onRead(NimBLECharacteristic* pCharacteristic){
    // Serial.print(pCharacteristic->getUUID().toString().c_str());
    // Serial.print(": onRead(), value: ");
    // Serial.println(pCharacteristic->getValue().c_str());
};

void CharacteristicCallbacks::onWrite(NimBLECharacteristic* pCharacteristic) {
    // Serial.print(pCharacteristic->getUUID().toString().c_str());
    // Serial.print(": onWrite(), value: ");
    // Serial.println(pCharacteristic->getValue().c_str());
};

void CharacteristicCallbacks::onNotify(NimBLECharacteristic* pCharacteristic) {
    // Serial.println("Sending notification to clients");
};

void CharacteristicCallbacks::onStatus(NimBLECharacteristic* pCharacteristic, Status status, int code) {
};

void CharacteristicCallbacks::onSubscribe(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc, uint16_t subValue) {
};

/* ====================================================================================================================== */
/** Descriptor コールバック クラス */
/* ====================================================================================================================== */

DescriptorCallbacks::DescriptorCallbacks(void) {
};

void DescriptorCallbacks::onWrite(NimBLEDescriptor* pDescriptor) {
    // std::string dscVal((char*)pDescriptor->getValue(), pDescriptor->getLength());
    // Serial.print("Descriptor witten value:");
    // Serial.println(dscVal.c_str());
};

void DescriptorCallbacks::onRead(NimBLEDescriptor* pDescriptor) {
    // Serial.print(pDescriptor->getUUID().toString().c_str());
    // Serial.println(" Descriptor read");
};

/* ====================================================================================================================== */
/** コネクションクラス */
/* ====================================================================================================================== */

BleConnectionStatus::BleConnectionStatus(void) {
};

void BleConnectionStatus::onConnect(NimBLEServer* pServer, ble_gap_conn_desc* desc)
{
  this->connected = true;
};

void BleConnectionStatus::onDisconnect(NimBLEServer* pServer, ble_gap_conn_desc* desc)
{
  this->connected = false;
};

/* ====================================================================================================================== */
/** Output コールバック クラス */
/* ====================================================================================================================== */

KeyboardOutputCallbacks::KeyboardOutputCallbacks(void) {
}

void KeyboardOutputCallbacks::onWrite(NimBLECharacteristic* me) {
  uint8_t* value = (uint8_t*)(me->getValue().c_str());
  ESP_LOGI(LOG_TAG, "special keys: %d", *value);
}


/* ====================================================================================================================== */
/** Remap Descriptor コールバック クラス */
/* ====================================================================================================================== */

RemapDescriptorCallbacks::RemapDescriptorCallbacks(void) {
};

void RemapDescriptorCallbacks::onWrite(NimBLEDescriptor* pDescriptor) {
    // std::string dscVal((char*)pDescriptor->getValue(), pDescriptor->getLength());
    // Serial.print("RemapDescriptorCallbacks: onWrite: ");
    // Serial.println(dscVal.c_str());
};

void RemapDescriptorCallbacks::onRead(NimBLEDescriptor* pDescriptor) {
    // Serial.print("RemapDescriptorCallbacks: onRead: ");
    // Serial.println(pDescriptor->getUUID().toString().c_str());
};


/* ====================================================================================================================== */
/** Remap Output コールバック クラス */
/* ====================================================================================================================== */


// ステップ分受信したか確認
int check_step() {
	int i, r = 0;
	for (i=0; i<8; i++) {
		if (save_step_flag[i]) r++;
	}
	return r;
};

RemapOutputCallbacks::RemapOutputCallbacks(void) {
	remap_change_flag = 0;
}


void RemapOutputCallbacks::onWrite(NimBLECharacteristic* me) {
	
}

// Remapにデータを返す
void RemapOutputCallbacks::sendRawData(uint8_t *data, uint8_t data_length) {
	this->pInputCharacteristic->setValue(data, data_length);
    this->pInputCharacteristic->notify();
	// delay(1);
}


/* ====================================================================================================================== */
/** HID RAW コールバック用 クラス */
/* ====================================================================================================================== */

void HidrawCallbackExec(int data_length) {

}
