/******************************************************************************
 *
 *  Copyright (C) 2018 ST Microelectronics S.A.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *
 ******************************************************************************/
#include "Iso13239CRC.h"

//************************************ Functions *******************************

/*******************************************************************************
**
** Function      computeCrc
**
** Description   Computes the 16-bit CRC of the specified function.
**
** Parameters    data - data to compute the CRC over.
**               len  - data length.
**
** Returns       CRC of the data. -1 if something went wrong.
**
*******************************************************************************/
uint16_t computeCrc(char* data, int len) {
  uint16_t tempCrc;

  tempCrc = (unsigned short)CRC_PRESET;

  int i, k;
  for (i = 0; i < len; i++) {
    tempCrc = tempCrc ^ ((unsigned short)(unsigned char)data[i]);
    for (k = 0; k < 8; k++) {
      if ((tempCrc & 0x0001) == 0x0001) {
        tempCrc = (tempCrc >> 1) ^ CRC_POLYNOMIAL;
      } else {
        tempCrc = tempCrc >> 1;
      }
    }
  }
  tempCrc = ~tempCrc;
  data[len] = (unsigned char)tempCrc;
  data[len + 1] = (unsigned char)(tempCrc >> 8);

  return tempCrc;
}
