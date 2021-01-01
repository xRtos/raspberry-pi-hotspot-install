#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf ("Usage: %s [ap-ssid] [ap-password]\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	char cmd[512];
	char cmd2[512];
	system("clear");
	printf("Updating System\n");
	system("sudo apt-get update -y");
	system("sudo apt-get upgrade -y");
	system("sudo apt-get install dnsmasq hostapd -y");
	system("sudo systemctl stop dnsmasq");
	system("sudo systemctl stop hostapd");
	printf("\nCreating a restore point");
	system("mkdir /etc/backup");
	system("cp /etc/dhcpcd.conf /etc/backup");
	system("cp /etc/dnsmasq.conf /etc/backup");
	system("cp /etc/hostapd/hostapd.conf /etc/backup");
	system("cp /etc/default/hostapd /etc/backup");
	system("cp /etc/sysctl.conf /etc/backup");
	system("clear");
	printf("\nConfiguring DHCPCD\n");
	system("rm -rf /etc/dhcpcd.conf");
	system("echo 'hostname' >> /etc/dhcpcd.conf");
	system("echo 'clientid' >> /etc/dhcpcd.conf");
	system("echo 'persistent' >> /etc/dhcpcd.conf");
	system("echo 'option rapid_commit' >> /etc/dhcpcd.conf");
	system("echo 'option domain_name_servers, domain_name, domain_search, host_name' >> /etc/dhcpcd.conf");
	system("echo 'option classless_static_routes' >> /etc/dhcpcd.conf");
	system("echo 'option ntp_servers' >> /etc/dhcpcd.conf");
	system("echo 'option interface_mtu' >> /etc/dhcpcd.conf");
	system("echo 'require dhcp_server_identifier' >> /etc/dhcpcd.conf");
	system("echo 'slaac private' >> /etc/dhcpcd.conf");
	system("echo 'interface wlan0' >> /etc/dhcpcd.conf");
	system("echo 'static ip_address=192.168.4.1/24' >> /etc/dhcpcd.conf");
	system("echo 'nohook wpa_supplicant' >> /etc/dhcpcd.conf");
	system("sudo service dhcpcd restart");
	system("sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig");
	printf("\nDoing Some More Configuring\n");
	system("echo 'interface=wlan0' >> /etc/dnsmasq.conf");
	system("echo 'dhcp-range=192.168.4.2,192.168.4.20,255.255.255.0,24h' >> /etc/dnsmasq.conf");
	printf("\nSetting Up hostapd.conf\n");
	system("rm -rf /etc/hostapd/hostapd.conf");
	system("echo 'interface=wlan0' >> /etc/hostapd/hostapd.conf");
	system("echo 'driver=nl80211' >> /etc/hostapd/hostapd.conf");
	sprintf(cmd, "echo 'ssid=%s' >> /etc/hostapd/hostapd.conf", argv[1]);
	system(cmd);
	system("echo 'hw_mode=g' >> /etc/hostapd/hostapd.conf");
	system("echo 'channel=7' >> /etc/hostapd/hostapd.conf");
	system("echo 'wmm_enabled=0' >> /etc/hostapd/hostapd.conf");
	system("echo 'macaddr_acl=0' >> /etc/hostapd/hostapd.conf");
	system("echo 'auth_algs=1' >> /etc/hostapd/hostapd.conf");
	system("echo 'ignore_broadcast_ssid=0' >> /etc/hostapd/hostapd.conf");
	system("echo 'wpa=2' >> /etc/hostapd/hostapd.conf");
	sprintf(cmd2, "echo 'wpa_passphrase=%s' >> /etc/hostapd/hostapd.conf", argv[2]);
	system(cmd2);
	system("echo 'wpa_key_mgmt=WPA-PSK' >> /etc/hostapd/hostapd.conf");
	system("echo 'wpa_pairwise=TKIP' >> /etc/hostapd/hostapd.conf");
	system("echo 'rsn_pairwise=CCMP' >> /etc/hostapd/hostapd.conf");
	printf("\nConfiguring...\n");
	system("rm -rf /etc/default/hostapd");
	system("echo 'DAEMON_CONF=\"/etc/hostapd/hostapd.conf\"' >> /etc/default/hostapd");
	printf("Starting Services...");
	system("sudo systemctl unmask hostapd");
	system("sudo systemctl enable hostapd");
	system("sudo systemctl start hostapd && sudo systemctl start dnsmasq");
	system("sudo systemctl start hostapd");
	system("sudo systemctl start dnsmasq");
	printf("Fixing tables");
	system("rm -rf /etc/sysctl.conf");
	system("echo 'net.ipv4.ip_forward=1' >> /etc/sysctl.conf");
	system("sudo iptables -t nat -A  POSTROUTING -o eth0 -j MASQUERADE");
	system("sudo sh -c \"iptables-save > /etc/iptables.ipv4.nat\"");
	system("iptables-restore < /etc/iptables.ipv4.nat");
	printf("Setup Finished!\n");
	printf("Rebooting In 3...");
	sleep(1);
	printf("Rebooting In 2...");
	sleep(1);
	printf("Rebooting In 1...");
	sleep(1);
	system("reboot");

}
