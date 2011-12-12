#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <netinet/ether.h>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cerr << "Syntaxe:\n\t" << argv[0] << " " << "adresa"
                << endl;
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        hostent *H = gethostbyname(argv[i]);
        if (H == NULL) {
            cerr << "Nepodařilo se zjistit adresu" << endl;
            return -1;
        }
        cout << "Oficiální jméno: " << H->h_name << endl;
        cout << "lternativni jmena (aliasy): " << endl;
        /* Budeme procházet pole H->h_aliases. Pole je ukončené NULL.*/
        char **alternativy = H->h_aliases;
        while (*alternativy != NULL) {
            cout << "\t" << *(alternativy++) << endl;
        }
        /* Budeme procházet pole H->h_addr_list. Pole je ukončené NULL. 
           Zvolíme jiný postup než v předchozím případě.*/
        cout << "IP adresy:" << endl;
        register int index = 0;
        while (H->h_addr_list[index] != NULL) {
            /* H->h_addr_list je binární forma IP adresy. Pro převod na
               tečkovou konvenci použijeme inet_ntoa.*/
            cout << "\t" << inet_ntoa(*(in_addr *) H->h_addr_list[index]);
            hostent *ip_name = gethostbyaddr(inet_ntoa(*(in_addr *) H->h_addr_list[index]), H->h_length, H->h_addrtype);
            if (ip_name != NULL) {
                cout << " " << ip_name->h_name;
            }
            cout << endl;
            index++;
        }

    }



    return 0;
}