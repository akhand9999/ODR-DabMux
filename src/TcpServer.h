/*
   Copyright (C) 2004, 2005, 2006, 2007, 2008, 2009 Her Majesty the Queen in
   Right of Canada (Communications Research Center Canada)
   */
/*
   This file is part of ODR-DabMux.

   ODR-DabMux is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   ODR-DabMux is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with ODR-DabMux.  If not, see <http://www.gnu.org/licenses/>.
   */

#ifndef _TCPSERVER
#define _TCPSERVER

#ifdef HAVE_CONFIG_H
#   include "config.h"
#endif

#include "InetAddress.h"
#ifdef _WIN32
# include <winsock.h>
# define socklen_t        int
# define reuseopt_t       char
#else
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <pthread.h>
# define SOCKET           int
# define INVALID_SOCKET   -1
# define SOCKET_ERROR     -1
# define reuseopt_t       int
#endif
//#define INVALID_PORT      -1

#include <iostream>
#include "TcpSocket.h"
//#include "SocketSelector.h"

/**
 *  This class represents a socket for sending and receiving UDP packets.
 *
 *  A UDP socket is the sending or receiving point for a packet delivery service.
 *  Each packet sent or received on a datagram socket is individually
 *  addressed and routed. Multiple packets sent from one machine to another may
 *  be routed differently, and may arrive in any order. 
 *  @author Pascal Charest pascal.charest@crc.ca
 */
class TcpServer {
  friend class SocketSelector;
public:
  TcpServer();
  TcpServer(int port, const char *name = NULL);
  ~TcpServer();
  
  static int init();
  static int clean();
  
  int create(int port, const char *name = NULL);
  int close();
  int listen();
  TcpSocket* accept();


 protected:
  /// The address on which the socket is binded.
  InetAddress address;
  /// The low-level socket used by system functions.
  SOCKET listenSocket;
};

#endif // _TCPSERVER
