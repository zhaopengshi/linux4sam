/*
 * Atmel WILC 802.11 b/g/n driver
 *
 * Copyright (c) 2015 Atmel Corportation
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "wilc_wlan_if.h"
#include "wilc_wlan.h"
#include "wilc_wlan_cfg.h"
#include "coreconfigurator.h"

struct wilc_mac_cfg_t {
	int mac_status;
	uint8_t mac_address[7];
	uint8_t ip_address[5];
	uint8_t bssid[7];
	uint8_t ssid[34];
	uint8_t firmware_version[129];
	uint8_t supp_rate[24];
	uint8_t wep_key[28];
	uint8_t i_psk[66];
	uint8_t hardwareProductVersion[33];
	uint8_t phyversion[17];
	uint8_t supp_username[21];
	uint8_t supp_password[64];
	uint8_t assoc_req[256];
	uint8_t assoc_rsp[256];
	uint8_t firmware_info[8];
	uint8_t scan_result[256];
	uint8_t scan_result1[256];
	uint8_t antenna_param[5];
};

static struct wilc_mac_cfg_t g_mac;

static struct wilc_cfg_byte_t g_cfg_byte[] = {
	{WID_BSS_TYPE, 0},
	{WID_CURRENT_TX_RATE, 0},
	{WID_CURRENT_CHANNEL, 0},
	{WID_PREAMBLE, 0},
	{WID_11G_OPERATING_MODE, 0},
	{WID_STATUS, 0},
	{WID_SCAN_TYPE, 0},
	{WID_KEY_ID, 0},
	{WID_QOS_ENABLE, 0},
	{WID_POWER_MANAGEMENT, 0},
	{WID_11I_MODE, 0},
	{WID_AUTH_TYPE, 0},
	{WID_SITE_SURVEY, 0},
	{WID_LISTEN_INTERVAL, 0},
	{WID_DTIM_PERIOD, 0},
	{WID_ACK_POLICY, 0},
	{WID_BCAST_SSID, 0},
	{WID_REKEY_POLICY, 0},
	{WID_SHORT_SLOT_ALLOWED, 0},
	{WID_START_SCAN_REQ, 0},
	{WID_RSSI, 0},
	{WID_LINKSPEED, 0},
	{WID_AUTO_RX_SENSITIVITY, 0},
	{WID_DATAFLOW_CONTROL, 0},
	{WID_SCAN_FILTER, 0},
	{WID_11N_PROT_MECH, 0},
	{WID_11N_ERP_PROT_TYPE, 0},
	{WID_11N_ENABLE, 0},
	{WID_11N_OPERATING_MODE, 0},
	{WID_11N_OBSS_NONHT_DETECTION, 0},
	{WID_11N_HT_PROT_TYPE, 0},
	{WID_11N_RIFS_PROT_ENABLE, 0},
	{WID_11N_SMPS_MODE, 0},
	{WID_11N_CURRENT_TX_MCS, 0},
	{WID_11N_SHORT_GI_ENABLE, 0},
	{WID_RIFS_MODE, 0},
	{WID_TX_ABORT_CONFIG, 0},
	{WID_11N_IMMEDIATE_BA_ENABLED, 0},
	{WID_11N_TXOP_PROT_DISABLE, 0},
	{WID_TX_POWER, 0},
	{WID_WOWLAN_TRIGGER, 0},
	{WID_NIL, 0}
};

static struct wilc_cfg_hword_t g_cfg_hword[] = {
	{WID_LINK_LOSS_THRESHOLD, 0},
	{WID_RTS_THRESHOLD, 0},
	{WID_FRAG_THRESHOLD, 0},
	{WID_SHORT_RETRY_LIMIT, 0},
	{WID_LONG_RETRY_LIMIT, 0},
	{WID_BEACON_INTERVAL, 0},
	{WID_ACTIVE_SCAN_TIME, 0},
	{WID_PASSIVE_SCAN_TIME, 0},
	{WID_SITE_SURVEY_SCAN_TIME, 0},
	{WID_JOIN_START_TIMEOUT, 0},
	{WID_AUTH_TIMEOUT, 0},
	{WID_ASOC_TIMEOUT, 0},
	{WID_11I_PROTOCOL_TIMEOUT, 0},
	{WID_EAPOL_RESPONSE_TIMEOUT, 0},
	{WID_11N_SIG_QUAL_VAL, 0},
	{WID_CCA_THRESHOLD, 0},
	{WID_NIL, 0}
};

static struct wilc_cfg_word_t g_cfg_word[] = {
	{WID_FAILED_COUNT, 0},
	{WID_RETRY_COUNT, 0},
	{WID_MULTIPLE_RETRY_COUNT, 0},
	{WID_FRAME_DUPLICATE_COUNT, 0},
	{WID_ACK_FAILURE_COUNT, 0},
	{WID_RECEIVED_FRAGMENT_COUNT, 0},
	{WID_MCAST_RECEIVED_FRAME_COUNT, 0},
	{WID_FCS_ERROR_COUNT, 0},
	{WID_SUCCESS_FRAME_COUNT, 0},
	{WID_TX_FRAGMENT_COUNT, 0},
	{WID_TX_MULTICAST_FRAME_COUNT, 0},
	{WID_RTS_SUCCESS_COUNT, 0},
	{WID_RTS_FAILURE_COUNT, 0},
	{WID_WEP_UNDECRYPTABLE_COUNT, 0},
	{WID_REKEY_PERIOD, 0},
	{WID_REKEY_PACKET_COUNT, 0},
	{WID_HW_RX_COUNT, 0},
	{WID_GET_INACTIVE_TIME, 0},
	{WID_NIL, 0}
};

static struct wilc_cfg_str_t g_cfg_str[] = {
	{WID_SSID, g_mac.ssid},			/* 33 + 1 bytes */
	{WID_FIRMWARE_VERSION, g_mac.firmware_version},
	{WID_OPERATIONAL_RATE_SET, g_mac.supp_rate},
	{WID_BSSID, g_mac.bssid},		/* 6 bytes */
	{WID_WEP_KEY_VALUE, g_mac.wep_key},	/* 27 bytes */
	{WID_11I_PSK, g_mac.i_psk},		/* 65 bytes */
	{WID_HARDWARE_VERSION, g_mac.hardwareProductVersion},
	{WID_MAC_ADDR, g_mac.mac_address},
	{WID_PHY_VERSION, g_mac.phyversion},
	{WID_SUPP_USERNAME, g_mac.supp_username},
	{WID_SUPP_PASSWORD, g_mac.supp_password},
	{WID_SITE_SURVEY_RESULTS, g_mac.scan_result},
	{WID_SITE_SURVEY_RESULTS, g_mac.scan_result1},
	{WID_ASSOC_REQ_INFO, g_mac.assoc_req},
	{WID_ASSOC_RES_INFO, g_mac.assoc_rsp},
	{WID_FIRMWARE_INFO, g_mac.firmware_version},
	{WID_IP_ADDRESS, g_mac.ip_address},
	{WID_NIL, NULL}
};

/*ATWILCSW-403*/
static wilc_cfg_bin_t g_cfg_bin[] = {
	{WID_ANTENNA_SELECTION, g_mac.antenna_param}
};
static int wilc_wlan_cfg_set_byte(uint8_t *frame, uint32_t offset,
				  uint16_t id, uint8_t val8)
{
	uint8_t *buf;

	if ((offset + 4) >= MAX_CFG_FRAME_SIZE)
		return 0;

	buf = &frame[offset];

	buf[0] = (uint8_t)id;
	buf[1] = (uint8_t)(id >> 8);
	buf[2] = 1;
	buf[3] = 0;
	buf[4] = val8;
	return 5;
}

static int wilc_wlan_cfg_set_hword(uint8_t *frame, uint32_t offset,
				   uint16_t id, uint16_t val16)
{
	uint8_t *buf;

	if ((offset + 5) >= MAX_CFG_FRAME_SIZE)
		return 0;

	buf = &frame[offset];

	buf[0] = (uint8_t)id;
	buf[1] = (uint8_t)(id >> 8);
	buf[2] = 2;
	buf[3] = 0;
	buf[4] = (uint8_t)val16;
	buf[5] = (uint8_t)(val16>>8);

	return 6;
}

static int wilc_wlan_cfg_set_word(uint8_t *frame, uint32_t offset,
				  uint16_t id, uint32_t val32)
{
	uint8_t *buf;

	if ((offset + 7) >= MAX_CFG_FRAME_SIZE)
		return 0;

	buf = &frame[offset];

	buf[0] = (uint8_t)id;
	buf[1] = (uint8_t)(id >> 8);
	buf[2] = 4;
	buf[3] = 0;
	buf[4] = (uint8_t)val32;
	buf[5] = (uint8_t)(val32>>8);
	buf[6] = (uint8_t)(val32>>16);
	buf[7] = (uint8_t)(val32>>24);

	return 8;
}

static int wilc_wlan_cfg_set_str(uint8_t *frame, uint32_t offset,
				 uint16_t id, uint8_t *str, uint32_t size)
{
	uint8_t *buf;

	if ((offset+size+4) >= MAX_CFG_FRAME_SIZE)
		return 0;

	buf = &frame[offset];

	buf[0] = (uint8_t)id;
	buf[1] = (uint8_t)(id >> 8);
	buf[2] = (uint8_t)size;
	buf[3] = (uint8_t)(size>>8);
	
	if((str != NULL) && (size != 0))
	{
		memcpy(&buf[4], str, size);
	}

	return (size+4);
}

static int wilc_wlan_cfg_set_bin(uint8_t *frame, uint32_t offset,
				 uint16_t id, uint8_t *b, uint32_t size)
{
	uint8_t *buf;
	uint32_t i;
	uint8_t checksum = 0;

	if ((offset + size + 5) >= MAX_CFG_FRAME_SIZE)
		return 0;

	buf = &frame[offset];
	buf[0] = (uint8_t)id;
	buf[1] = (uint8_t)(id >> 8);
	buf[2] = (uint8_t)size;
	buf[3] = (uint8_t)(size >> 8);

	if ((b != NULL) && (size != 0))	{
		memcpy(&buf[4], b, size);
		for (i = 0; i < size; i++)
			checksum += buf[i + 4];
	}

	buf[size + 4] = checksum;

	return (size + 5);
}

static void wilc_wlan_parse_response_frame(uint8_t *info, int size)
{
	uint32_t wid, len = 0, i;
	static int seq;

	while (size > 0) {
		i = 0;
		wid = info[0] | (info[1] << 8);
	#ifdef BIG_ENDIAN
		wid = BYTE_SWAP(wid);
	#endif
		PRINT_INFO(GENERIC_DBG,"Processing response for %d seq %d\n", wid, seq++);
		switch ((wid >> 12) & 0x7) {
			case WID_CHAR:
				do {
					if (g_cfg_byte[i].id == WID_NIL)
						break;

					if (g_cfg_byte[i].id == wid) {
						g_cfg_byte[i].val = info[4];
						break;
					}
					i++;
				} while (1);
				len = 3;
				break;
			case WID_SHORT:
				do {
					if (g_cfg_hword[i].id == WID_NIL)
						break;

					if (g_cfg_hword[i].id == wid) {
#ifdef BIG_ENDIAN
						g_cfg_hword[i].val = (info[4]<<8)|(info[5]);
#else
						g_cfg_hword[i].val = info[4]|(info[5]<<8);
#endif
						break;
					}
					i++;
				} while (1);
				len = 4;
				break;
			case WID_INT:
				do {
					if (g_cfg_word[i].id == WID_NIL)
						break;

					if (g_cfg_word[i].id == wid) {
#ifdef BIG_ENDIAN
						g_cfg_word[i].val = (info[4]<<24)|(info[5]<<16)|(info[6]<<8)|(info[7]);
#else
						g_cfg_word[i].val = info[4]|(info[5]<<8)|(info[6]<<16)|(info[7]<<24);
#endif
						break;
					}
					i++;
				} while (1);
				len = 6;
				break;
			case WID_STR:
				do {
					if (g_cfg_str[i].id == WID_NIL)
						break;

					if (g_cfg_str[i].id == wid) {
						if (wid == WID_SITE_SURVEY_RESULTS) {
							static int toggle;

							PRINT_INFO(GENERIC_DBG,"Site survey results received %d\n",
								   size);

							PRINT_INFO(GENERIC_DBG,"Site survey results value %d toggle%d\n", size, toggle);
							i += toggle;
							toggle ^= 1;
						}
						memcpy(g_cfg_str[i].str, &info[2], (2+((info[3] << 8) | info[2])));
						break;
					}
					i++;
				} while (1);
				len = 2+((info[3] << 8) | info[2]);
				break;

			/*ATWILCSW-403*/
			case WID_BIN_DATA:
				do {
					if (g_cfg_bin[i].id == WID_NIL)
						break;

					if (g_cfg_bin[i].id == wid)
					{
			             uint16_t length      = ((info[3] << 8) | info[2]);
               			 uint8_t  checksum    = 0;
						uint16_t i           = 0;
						 
					/* Compute the Checksum of received data field */
                    for(i = 0;i < length;i++)
                    {
                        checksum += info[4 + i];
                    }
					/* ATWILCSW-491 - Verify the checksum of recieved BIN DATA */
						if (checksum == info[4 + length])
						{
						memcpy(g_cfg_bin[i].bin, &info[2], length + 2);
							len = 2 + length + 1;   /* value length + data length + checksum */
						break;
						}
					else
						{
							PRINT_ER("Parsing WID_BIN_DATA - Checksum Failed!" );
							return;
						}
					} 
					i++;
				} while (1);
				
				break;
				
			default:
				break;
		}
		size -= (2 + len);
		info += (2 + len);
	}
}

static int wilc_wlan_parse_info_frame(uint8_t *info, int size)
{
	struct wilc_mac_cfg_t *pd = (struct wilc_mac_cfg_t *)&g_mac;
	uint32_t wid, len;
	int type = WILC_CFG_RSP_STATUS;

	wid = info[0] | (info[1] << 8);
	len = info[2];
	PRINT_INFO(GENERIC_DBG,"Status Len = %d Id= %d\n", len, wid);
	if ((len == 1) && (wid == WID_STATUS)) {
		pd->mac_status = info[3];
		type = WILC_CFG_RSP_STATUS;
	}

	return type;
}

static int wilc_wlan_cfg_set_wid(uint8_t *frame, uint32_t offset,
				 uint16_t id, uint8_t *buf, int size)
{
	uint8_t type = (id >> 12) & 0xf;
	int ret = 0;

	if (type == 0) {	/* byte command */
		if (size >= 1)
			ret = wilc_wlan_cfg_set_byte(frame, offset, id, *buf);
	} else if (type == 1) {	/* half word command */
		if (size >= 2)
			ret = wilc_wlan_cfg_set_hword(frame, offset,
						      id, *((uint16_t *)buf));
	} else if (type == 2) {	/* word command */
		if (size >= 4)
			ret = wilc_wlan_cfg_set_word(frame, offset,
						     id, *((uint32_t *)buf));
	} else if (type == 3) {	/* string command */
		ret = wilc_wlan_cfg_set_str(frame, offset, id, buf, size);
	} else if (type == 4) {	/* binary command */
		ret = wilc_wlan_cfg_set_bin(frame, offset, id, buf, size);
	} else {
		PRINT_ER("illegal id\n");
	}
	return ret;
}

static int wilc_wlan_cfg_get_wid(uint8_t *frame, uint32_t offset, uint16_t id)
{
	uint8_t *buf;

	if ((offset + 2) >= MAX_CFG_FRAME_SIZE)
		return 0;

	buf = &frame[offset];

	buf[0] = (uint8_t)id;
	buf[1] = (uint8_t)(id >> 8);

	return 2;
}

static int wilc_wlan_cfg_get_wid_value(uint16_t wid, uint8_t *buffer,
				       uint32_t buffer_size)
{
	uint32_t type = (wid >> 12) & 0xf;
	int i, ret = 0;

	if (wid == WID_STATUS) {
		*((uint32_t *)buffer) = g_mac.mac_status;
		return 4;
	}

	i = 0;
	if (type == 0) {	/* byte command */
		do {
			if (g_cfg_byte[i].id == WID_NIL)
				break;

			if (g_cfg_byte[i].id == wid) {
				memcpy(buffer,  &g_cfg_byte[i].val, 1);
				ret = 1;
				break;
			}
			i++;
		} while (1);
	} else if (type == 1) {	/* half word command */
		do {
			if (g_cfg_hword[i].id == WID_NIL)
				break;

			if (g_cfg_hword[i].id == wid) {
				memcpy(buffer,  &g_cfg_hword[i].val, 2);
				ret = 2;
				break;
			}
			i++;
		} while (1);
	} else if (type == 2) {	/* word command */
		do {
			if (g_cfg_word[i].id == WID_NIL)
				break;

			if (g_cfg_word[i].id == wid) {
				memcpy(buffer,  &g_cfg_word[i].val, 4);
				ret = 4;
				break;
			}
			i++;
		} while (1);
	} else if (type == 3) {	/* string command */
		do {
			if (g_cfg_str[i].id == WID_NIL)
				break;

			if (g_cfg_str[i].id == wid) {
				uint32_t size =  (g_cfg_str[i].str[0])|(g_cfg_str[i].str[1]<<8);

				if (buffer_size >= size) {
					if (g_cfg_str[i].id == WID_SITE_SURVEY_RESULTS)	{
						static int toggle;

						PRINT_INFO(GENERIC_DBG,"Site survey results%d\n",
							 size);
						i += toggle;
						toggle ^= 1;
					}
					memcpy(buffer,  &g_cfg_str[i].str[2], size);
					ret = size;
				}
				break;
			}
			i++;
		} while (1);
	}else if (type == 4) {			/* binary command */
		do {
			if (g_cfg_bin[i].id == WID_NIL)
				break;

			if (g_cfg_bin[i].id == wid) {
				uint32_t size =  (g_cfg_bin[i].bin[0])|(g_cfg_bin[i].bin[1]<<8);
				if (buffer_size >= size) {					
					memcpy(buffer,  &g_cfg_bin[i].bin[2], size);
					ret = size;
				}
				break;
			}
			i++;
		} while (1);
	} else {
		PRINT_ER("[CFG]: illegal type (%08x)\n", wid);
	}
	return ret;
}

static int wilc_wlan_cfg_indicate_rx(uint8_t *frame, int size, struct wilc_cfg_rsp *rsp)
{
	int ret = 1;
	uint8_t msg_type;
	uint8_t msg_id;
	uint16_t msg_len;

	msg_type = frame[0];
	msg_id = frame[1];	/* seq no */
#ifdef BIG_ENDIAN
	msg_len = (frame[2] << 8) | frame[3];
#else
	msg_len = (frame[3] << 8) | frame[2];
#endif
	frame += 4;
	size -= 4;

	/*
	 * The valid types of response messages
	 * are 'R' (Response), 'I' (Information), and 'N' (Network Information)
	 */
	switch (msg_type) {
	case 'R':
		wilc_wlan_parse_response_frame(frame, size);
		rsp->type = WILC_CFG_RSP;
		rsp->seq_no = msg_id;
		break;

	case 'I':
		rsp->type = wilc_wlan_parse_info_frame(frame, size);
		rsp->seq_no = msg_id;
		/* call host interface info parse as well */
		PRINT_INFO(RX_DBG,"Info message received\n");
		GnrlAsyncInfoReceived(frame - 4, size + 4);
		break;
	case 'L':
		PRINT_ER("Unexpected firmware log message received\n");
	case 'N':
		NetworkInfoReceived(frame - 4, size + 4);
		rsp->type = 0;
		break;
	case 'S':
		PRINT_INFO(RX_DBG,"Scan Notification Received\n");
		host_int_ScanCompleteReceived(frame - 4, size + 4);
		break;
	default:
		PRINT_INFO(RX_DBG,"Receive unknown message type %d-%d-%d-%d-%d-%d-%d-%d\n",
			 frame[0], frame[1], frame[2], frame[3], frame[4],
			 frame[5], frame[6], frame[7]);
		rsp->type = 0;
		rsp->seq_no = msg_id;
		ret = 0;
		break;
	}

	return ret;
}

static int wilc_wlan_cfg_init(void)
{
	memset((void *)&g_mac, 0, sizeof(struct wilc_mac_cfg_t));
	return 1;
}

struct wilc_cfg_func mac_cfg = {
	wilc_wlan_cfg_set_wid,
	wilc_wlan_cfg_get_wid,
	wilc_wlan_cfg_get_wid_value,
	wilc_wlan_cfg_indicate_rx,
	wilc_wlan_cfg_init,
};
