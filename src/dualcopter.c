/*
 * Main controller for Multiwii controlled dualcopter
 * Copyright (c) 2015 Michael Carter
 *
 * zerosignal1982@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "mwsp/mwsp.h"
#include "mwsp/mwsp_util.h"

void usage(char *argv[]) {
    fprintf(stderr, "Usage: %s -s <serial_port>\n", argv[0]);
}

/* main */
int main(int argc, char *argv[])
{
    int opt, fd;
    char *serial_port;

    if(argc != 3){
        usage(argv);
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch(opt) {
            case 's':
                serial_port = malloc(sizeof(char) * (strlen(optarg) + 1));
                strncpy(serial_port, optarg, strlen(optarg));

                break;
            default:
                usage(argv);
                exit(EXIT_FAILURE);
        }
    }

    /*------------------------------------------------------*/

    printf("Connecting to flight controller\n");

    /* connect the flight controller */
    fd = mwsp_connect(serial_port);
    if(fd < 0){
        perror("Failed to connect to serial port"); 
        exit(-1);
    }

    /*------------------------------------------------------*/

    printf("Disconnecting from flight controller\n");

    /* disconnect the flight controller */
    if(mwsp_disconnect(fd) < 0){
        printf("Something went wrong disconnecting!\n");
        exit(-2);
    }
}
