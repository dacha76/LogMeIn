/************************************************************\
 * File: test_lib.c
 * 
 * Description: 
 * 
 * This file contains test cases resources and functions.
 * 
\************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/server_test.h"
#include "../../include/server_test_rc.h"
#include "../../include/server_test_client.h"

///////////////////// DEFINITIONS //////////////////////////

#define cTEST_LIB_MAX_AOR_CASES     8

/////////////////////// GLOBALS ////////////////////////////

tTEST_CLIENT_CASE_AOR g_aorTestCases[] = {
    {{"0142e2fa3543cb32bf000100620002"},{"{\"addressOfRecord\":\"0142e2fa3543cb32bf000100620002\",\"tenantId\":\"0127d974-f9f3-0704-2dee-000100420001\",\"uri\":\"sip:0142e2fa3543cb32bf000100620002@109.149.135.172;jbcuser=cpe70\",\"contact\":\"<sip:0142e2fa3543cb32bf000100620002@207.169.118.8;jbcuser=cpe70>;methods=\\\"INVITE, ACK, BYE, CANCEL, OPTIONS, INFO, MESSAGE, SUBSCRIBE, NOTIFY, PRACK, UPDATE, REFER\\\"\",\"path\":[\"<sip:Mi0xOTkuMTkyLjE2NS4xOTQtMTk2MjI@8.63.250.250:5060;lr>\"],\"source\":\"29.211.204.173:19622\",\"target\":\"60.124.57.147:5061\",\"userAgent\":\"polycom.vvx.600\",\"rawUserAgent\":\"PolycomVVX-VVX_600-UA/132.244.41.145\",\"created\":\"2016-12-12T22:40:40.764Z\",\"lineId\":\"013db2ba-2175-6d29-6157-000100620002\"}"}} ,
    {{"4zTeEvZtaCrV0iz4DQZDvGdMnK9ury"},{"{\"addressOfRecord\":\"4zTeEvZtaCrV0iz4DQZDvGdMnK9ury\",\"tenantId\":\"0127d974-f9f3-0704-2dee-000100420001\",\"uri\":\"sip:4zTeEvZtaCrV0iz4DQZDvGdMnK9ury@88.21.47.175\",\"contact\":\"<sip:4zTeEvZtaCrV0iz4DQZDvGdMnK9ury@105.2.98.174>;methods=\\\"INVITE, ACK, BYE, CANCEL, OPTIONS, INFO, MESSAGE, SUBSCRIBE, NOTIFY, PRACK, UPDATE, REFER\\\"\",\"path\":[\"<sip:Mi0xNjYuNzAuNy4yLTUzOTk@188.83.33.227:5060;lr>\"],\"source\":\"25.151.55.237:5399\",\"target\":\"76.252.62.138:5061\",\"userAgent\":\"polycom.vvx.600\",\"rawUserAgent\":\"PolycomVVX-VVX_600-UA/97.162.210.78\",\"created\":\"2016-12-18T08:31:26.695Z\",\"lineId\":\"01491f6d-825d-a819-7b00-000100620002\"}"}} ,
    {{"ocsSW37nqHYgfTPWKIBpIToMcxMgFJ"},{"{\"addressOfRecord\":\"ocsSW37nqHYgfTPWKIBpIToMcxMgFJ\",\"tenantId\":\"014ff6ef-db54-15cc-f852-000100420002\",\"uri\":\"sip:ocsSW37nqHYgfTPWKIBpIToMcxMgFJ@161.50.177.222\",\"contact\":\"<sip:ocsSW37nqHYgfTPWKIBpIToMcxMgFJ@12.22.206.100>;methods=\\\"INVITE, ACK, BYE, CANCEL, OPTIONS, INFO, MESSAGE, SUBSCRIBE, NOTIFY, PRACK, UPDATE, REFER\\\"\",\"path\":[\"<sip:MS0xOTkuODcuMTIwLjEyOS05MTE4@3.177.158.139:5060;lr>\"],\"source\":\"198.247.37.8:9118\",\"target\":\"50.148.218.175:5060\",\"userAgent\":\"polycom.soundpointip.335\",\"rawUserAgent\":\"PolycomSoundPointIP-SPIP_335-UA/203.223.148.68\",\"created\":\"2016-12-23T17:11:20.380Z\",\"lineId\":\"25226f25-67c7-49b0-916f-d4702e765ef4\"}"}} ,
    {{"015314b84ed3497ff9000100620007"},{"{\"addressOfRecord\":\"015314b84ed3497ff9000100620007\",\"tenantId\":\"0127d974-f9f3-0704-2dee-000100420001\",\"uri\":\"sip:015314b84ed3497ff9000100620007@176.117.251.153\",\"contact\":\"<sip:015314b84ed3497ff9000100620007@140.108.10.151>;methods=\\\"INVITE, ACK, BYE, CANCEL, OPTIONS, INFO, MESSAGE, SUBSCRIBE, NOTIFY, PRACK, UPDATE, REFER\\\"\",\"path\":[\"<sip:Mi0xOTkuMTkyLjE2NS4xOTQtODY0Ng@212.55.173.146:5060;lr>\"],\"source\":\"6.50.77.138:8646\",\"target\":\"141.139.141.9:5061\",\"userAgent\":\"polycom.soundpointip.335\",\"rawUserAgent\":\"PolycomSoundPointIP-SPIP_335-UA/66.85.169.156\",\"created\":\"2016-12-30T07:54:43.218Z\",\"lineId\":\"0153108b-93c6-8987-0ff9-000100620007\"}"}} ,
    {{"0148fc1ae62d4ce781000100620005"},{"{\"addressOfRecord\":\"0148fc1ae62d4ce781000100620005\",\"tenantId\":\"0127d974-f9f3-0704-2dee-000100420001\",\"uri\":\"sip:0148fc1ae62d4ce781000100620005@159.197.30.116\",\"contact\":\"<sip:0148fc1ae62d4ce781000100620005@227.182.191.98>;methods=\\\"INVITE, ACK, BYE, CANCEL, OPTIONS, INFO, MESSAGE, SUBSCRIBE, NOTIFY, PRACK, UPDATE, REFER\\\"\",\"path\":[\"<sip:Mi0xOTkuMTkyLjE2NS4xOTQtODg2NQ@89.116.98.164:5060;lr>\"],\"source\":\"149.37.194.67:8865\",\"target\":\"222.211.233.105:5061\",\"userAgent\":\"polycom.soundpointip.550\",\"rawUserAgent\":\"PolycomSoundPointIP-SPIP_550-UA/24.115.185.139\",\"created\":\"2016-12-30T07:55:06.454Z\",\"lineId\":\"0148fbe4-961b-f9e1-4781-000100620005\"}"}} ,
    {{"014ee51b31b35070f0000100620002"},{"{\"addressOfRecord\":\"014ee51b31b35070f0000100620002\",\"tenantId\":\"0127d974-f9f3-0704-2dee-000100420001\",\"uri\":\"sip:014ee51b31b35070f0000100620002@230.11.178.29\",\"contact\":\"<sip:014ee51b31b35070f0000100620002@157.83.168.47>;methods=\\\"INVITE, ACK, BYE, CANCEL, OPTIONS, INFO, MESSAGE, SUBSCRIBE, NOTIFY, PRACK, UPDATE, REFER\\\"\",\"path\":[\"<sip:Mi03MC4xMjIuMjEyLjE4OC01MDYw@150.164.228.117:5060;lr>\"],\"source\":\"129.213.239.124:5060\",\"target\":\"196.174.54.44:5061\",\"userAgent\":\"polycom.vvx.400\",\"rawUserAgent\":\"PolycomVVX-VVX_400-UA/36.74.191.132\",\"created\":\"2017-01-04T03:13:59.925Z\",\"lineId\":\"014846b0-e4d1-0973-f9f3-000100620005\"}"}} ,
    {{"S0S83Dr8FFBEY7YOtVVRZ84J4heosh"},{"{\"addressOfRecord\":\"S0S83Dr8FFBEY7YOtVVRZ84J4heosh\",\"tenantId\":\"01554acd-2f0b-5556-9bab-000100420009\",\"uri\":\"sip:S0S83Dr8FFBEY7YOtVVRZ84J4heosh@233.33.35.115\",\"contact\":\"\\\"1002\\\" <sip:S0S83Dr8FFBEY7YOtVVRZ84J4heosh@88.7.144.93>\",\"path\":[\"<sip:Mi02OS43MC4xMTQuMi0xMTAz@175.254.139.75:5060;lr>\"],\"source\":\"0.114.68.182:1103\",\"target\":\"121.97.126.168:5061\",\"userAgent\":\"linksys.spa.525g\",\"rawUserAgent\":\"Cisco/SPA525G2-7.5.7\",\"created\":\"2017-01-06T12:19:19.142Z\",\"lineId\":\"01554b0b-e341-22a3-45a5-000100620009\"}`"}} ,
    {{"01546f59a9033db700000100610001"},{"{\"addressOfRecord\":\"01546f59a9033db700000100610001\",\"tenantId\":\"0127d974-f9f3-0704-2dee-000100420001\",\"uri\":\"sip:01546f59a9033db700000100610001@0.126.229.77:10902\",\"contact\":\"<sip:01546f59a9033db700000100610001@43.82.170.192:10902>;+sip.instance=\\\"<urn:uuid:58B7D3C8-145E-00EC-5FC2-861E57FD7FB2>\\\"\",\"path\":[\"<sip:Mi0xNzQuMTM0LjE0Ni4xODktMTA5MDI@200.59.12.96:5060;lr>\"],\"source\":\"238.116.236.172:10902\",\"target\":\"34.92.40.2:5061\",\"userAgent\":null,\"rawUserAgent\":\"Jive iOS Client\",\"created\":\"2017-01-06T13:25:25.539Z\",\"lineId\":\"01464e4a-6568-854b-fc96-000100620002\"}"}} ,
    };

/////////////////////// FUNCTIONS //////////////////////////
