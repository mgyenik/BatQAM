
int cdcacm_control_request(usbd_device *usbd_dev,
	struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
	void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req));

void cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep);
void cdcacm_set_config(usbd_device *usbd_dev, uint16_t wValue);

#include <libopencm3/usb/cdc.h>

struct cdc_func_desc {
	struct usb_cdc_header_descriptor header;
	struct usb_cdc_call_management_descriptor call_mgmt;
	struct usb_cdc_acm_descriptor acm;
	struct usb_cdc_union_descriptor cdc_union;
} __attribute__((packed));

extern const struct usb_device_descriptor dev;
extern const struct usb_endpoint_descriptor comm_endp[];
extern const struct usb_endpoint_descriptor data_endp[];
extern const struct usb_interface_descriptor comm_iface[];
extern const struct usb_interface_descriptor data_iface[];
extern const struct cdc_func_desc cdcacm_functional_descriptors;
extern const struct usb_interface ifaces[];
extern const struct usb_config_descriptor config;
extern const char * usb_strings[];
extern uint8_t usbd_control_buffer[128];
