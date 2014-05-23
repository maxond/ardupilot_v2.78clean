// MESSAGE THERMO_GYRO_SWITCH PACKING

#define MAVLINK_MSG_ID_THERMO_GYRO_SWITCH 195

typedef struct __mavlink_thermo_gyro_switch_t
{
 uint32_t time_boot_ms; ///< Timestamp (milliseconds since system boot)
 uint8_t control_switch; ///< Toggles 0 for gyro and 1 for thermo
} mavlink_thermo_gyro_switch_t;

#define MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN 5
#define MAVLINK_MSG_ID_195_LEN 5

#define MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_CRC 201
#define MAVLINK_MSG_ID_195_CRC 201



#define MAVLINK_MESSAGE_INFO_THERMO_GYRO_SWITCH { \
	"THERMO_GYRO_SWITCH", \
	2, \
	{  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_thermo_gyro_switch_t, time_boot_ms) }, \
         { "control_switch", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_thermo_gyro_switch_t, control_switch) }, \
         } \
}


/**
 * @brief Pack a thermo_gyro_switch message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param control_switch Toggles 0 for gyro and 1 for thermo
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thermo_gyro_switch_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_boot_ms, uint8_t control_switch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint8_t(buf, 4, control_switch);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#else
	mavlink_thermo_gyro_switch_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.control_switch = control_switch;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_THERMO_GYRO_SWITCH;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#endif
}

/**
 * @brief Pack a thermo_gyro_switch message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param control_switch Toggles 0 for gyro and 1 for thermo
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thermo_gyro_switch_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_boot_ms,uint8_t control_switch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint8_t(buf, 4, control_switch);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#else
	mavlink_thermo_gyro_switch_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.control_switch = control_switch;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_THERMO_GYRO_SWITCH;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#endif
}

/**
 * @brief Encode a thermo_gyro_switch struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param thermo_gyro_switch C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thermo_gyro_switch_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_thermo_gyro_switch_t* thermo_gyro_switch)
{
	return mavlink_msg_thermo_gyro_switch_pack(system_id, component_id, msg, thermo_gyro_switch->time_boot_ms, thermo_gyro_switch->control_switch);
}

/**
 * @brief Encode a thermo_gyro_switch struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param thermo_gyro_switch C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thermo_gyro_switch_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_thermo_gyro_switch_t* thermo_gyro_switch)
{
	return mavlink_msg_thermo_gyro_switch_pack_chan(system_id, component_id, chan, msg, thermo_gyro_switch->time_boot_ms, thermo_gyro_switch->control_switch);
}

/**
 * @brief Send a thermo_gyro_switch message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param control_switch Toggles 0 for gyro and 1 for thermo
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_thermo_gyro_switch_send(mavlink_channel_t chan, uint32_t time_boot_ms, uint8_t control_switch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint8_t(buf, 4, control_switch);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH, buf, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH, buf, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#endif
#else
	mavlink_thermo_gyro_switch_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.control_switch = control_switch;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH, (const char *)&packet, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH, (const char *)&packet, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_thermo_gyro_switch_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, uint8_t control_switch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint8_t(buf, 4, control_switch);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH, buf, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH, buf, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#endif
#else
	mavlink_thermo_gyro_switch_t *packet = (mavlink_thermo_gyro_switch_t *)msgbuf;
	packet->time_boot_ms = time_boot_ms;
	packet->control_switch = control_switch;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH, (const char *)packet, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH, (const char *)packet, MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE THERMO_GYRO_SWITCH UNPACKING


/**
 * @brief Get field time_boot_ms from thermo_gyro_switch message
 *
 * @return Timestamp (milliseconds since system boot)
 */
static inline uint32_t mavlink_msg_thermo_gyro_switch_get_time_boot_ms(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field control_switch from thermo_gyro_switch message
 *
 * @return Toggles 0 for gyro and 1 for thermo
 */
static inline uint8_t mavlink_msg_thermo_gyro_switch_get_control_switch(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Decode a thermo_gyro_switch message into a struct
 *
 * @param msg The message to decode
 * @param thermo_gyro_switch C-struct to decode the message contents into
 */
static inline void mavlink_msg_thermo_gyro_switch_decode(const mavlink_message_t* msg, mavlink_thermo_gyro_switch_t* thermo_gyro_switch)
{
#if MAVLINK_NEED_BYTE_SWAP
	thermo_gyro_switch->time_boot_ms = mavlink_msg_thermo_gyro_switch_get_time_boot_ms(msg);
	thermo_gyro_switch->control_switch = mavlink_msg_thermo_gyro_switch_get_control_switch(msg);
#else
	memcpy(thermo_gyro_switch, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_THERMO_GYRO_SWITCH_LEN);
#endif
}
