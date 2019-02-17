#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
		char cmd[512];
		char cmd2[512];
		system("clear");
		printf("Stopping Services");
		system("sudo systemctl stop dnsmasq");
		system("sudo systemctl stop hostapd");
		printf("Restoring Files...");
		sleep(1);
		system("cp /etc/backup/dhcpcd.conf /etc/dhcpcd.conf");
		system("cp /etc/backup/dnsmasq.conf /etc/dnsmasq.conf");
		system("cp /etc/backup/hostapd.conf /etc/hostapd/hostapd.conf");
		system("cp /etc/backup/hostapd /etc/default/hostapd");
		system("cp /etc/backup/sysctl.conf /etc/sysctl.conf");
		printf("Fixing Tables...");
		sleep(1);
		system("iptables -F");
		system("sudo service dhcpcd restart");
}