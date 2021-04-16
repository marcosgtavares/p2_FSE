#include "../inc/bme280.h"
#include "../inc/bme280_i2c.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <signal.h>




int fd;
int time=0;

struct param_adress{
	float temp;
	float hum;
};

void timer(int signum){
	printf("YAY");
	time=1;
}

void user_delay_ms(uint32_t period, void *intf_ptr){
  	usleep(period*1000);
}

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr){
	write(fd, &reg_addr,1);
	read(fd, reg_data, len);
	return 0;
}

int8_t user_i2c_write(uint8_t reg_addr, const unsigned char *reg_data, uint32_t len, void *intf_ptr){
	uint8_t *buf;
	buf = malloc(len +1);
	buf[0] = reg_addr;
	memcpy(buf +1, reg_data, len);
	write(fd, buf, len +1);
	free(buf);
	return 0;
}
int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev){
	int8_t rslt;
	uint8_t settings_sel;
	//struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	return rslt;
}

struct bme280_dev* init_sensor(){
    int8_t rslt = BME280_OK;
    uint8_t dev_addr = BME280_I2C_ADDR_PRIM;
    struct bme280_dev *dev=(struct bme280_dev *)malloc(sizeof(struct bme280_dev));
	fd = wiringPiI2CSetup(0x76);

    dev->intf_ptr = &dev_addr;
    dev->intf = BME280_I2C_INTF;
    dev->read = &user_i2c_read;
    dev->write = &user_i2c_write;
    dev->delay_us = &user_delay_ms;
    
    rslt = bme280_init(dev);
    return dev;
}

int set_i2c_addr_sensor(){
  	fd = wiringPiI2CSetup(0x76);
	return fd;
}

void *req_temp_hum(void *th){
	struct bme280_data comp_data;
	struct bme280_dev *dev;

	signal(SIGALRM, timer);

    dev = init_sensor();
    int rslt = stream_sensor_data_normal_mode(dev);//Inicialização e configuração inicial do sensor bme280
    dev->delay_us(100, dev->intf_ptr);
    int fd_bme280;
	fd_bme280=set_i2c_addr_sensor();//Abre a porta do sensor bme280

	
    while(1){
		if(time==1){
			alarm(1);
			time=0;
			rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
			((struct param_adress *)th)->temp = (float)comp_data.temperature;
			((struct param_adress *)th)->hum = (float)comp_data.humidity;

			printf("|%f||%f|\n", (float)comp_data.temperature,(float)comp_data.humidity );
		}
	}	
}

void precocious_req(float *temp, float *hum){
	struct bme280_data comp_data;
	struct bme280_dev *dev;

	signal(SIGALRM, timer);

    dev = init_sensor();
    int rslt = stream_sensor_data_normal_mode(dev);//Inicialização e configuração inicial do sensor bme280
    dev->delay_us(100, dev->intf_ptr);
    int fd_bme280;
	fd_bme280=set_i2c_addr_sensor();//Abre a porta do sensor bme280
	rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
	*temp = comp_data.temperature;
	*hum = comp_data.humidity;
	close(fd_bme280);
	free(dev);
}