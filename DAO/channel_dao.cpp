#include "channel_dao.h"

Channel_DAO::Channel_DAO(QObject *parent)
    : QObject{parent}
{}

channel Channel_DAO::dataToObj0x40(QByteArray data)
{
    cl.setStartBit1(data[0]);
    cl.setStartBit2(data[1]);
    cl.setStartBit3(data[2]);
    cl.setStartBit4(data[3]);

    cl.setSize(data[4]);

    cl.setCommand(data[5]);

    cl.setChannelHigh(data[6]);
    cl.setChannelLow(data[7]);

    cl.setVfoaMode(data[8]);
    cl.setVfobMode(data[9]);

    // 获取VFOA频率
    cl.setVfoaFrequency1(data[10]);
    cl.setVfoaFrequency2(data[11]);
    cl.setVfoaFrequency3(data[12]);
    cl.setVfoaFrequency4(data[13]);
    // 获取VFOB频率
    cl.setVfobFrequency1(data[14]);
    cl.setVfobFrequency2(data[15]);
    cl.setVfobFrequency3(data[16]);
    cl.setVfobFrequency4(data[17]);
    // 亚音
    cl.setEmitYayin(data[18]);
    cl.setReceiveYayin(data[19]);

    // 获取信道名字
    int size = data.size();
    QByteArray name;
    name.resize((size-2)-20);
    int j = 0;
    for(int i = 20 ; i < (size-2) ; i++,j++){
        name[j] = data[i];
    }
    cl.setChannelName(name);

    // 获取crc
    cl.setCrcHigh(data[size-2]);
    cl.setCrcLow(data[size-1]);

    return cl;
}

channel Channel_DAO::dataToObj0x41(QByteArray data)
{
    cl.setStartBit1(data[0]);
    cl.setStartBit2(data[1]);
    cl.setStartBit3(data[2]);
    cl.setStartBit4(data[3]);

    cl.setSize(data[4]);

    cl.setCommand(data[5]);

    cl.setChannelHigh(data[6]);
    cl.setChannelLow(data[7]);

    cl.setVfoaMode(data[8]);
    cl.setVfobMode(data[9]);

    cl.setVfoaFrequency1(data[10]);
    cl.setVfoaFrequency2(data[11]);
    cl.setVfoaFrequency3(data[12]);
    cl.setVfoaFrequency4(data[13]);

    cl.setVfobFrequency1(data[14]);
    cl.setVfobFrequency2(data[15]);
    cl.setVfobFrequency3(data[16]);
    cl.setVfobFrequency4(data[17]);
    cl.setEmitYayin(data[18]);
    cl.setReceiveYayin(data[19]);
    // 获取信道名字
    int size = data.size();

    QByteArray name;
    name.resize((size-2)-20);
    int j = 0;
    for(int i = 20 ; i < (size-2) ; i++,j++){
        name[j] = data[i];
    }
    cl.setChannelName(name);

    // 获取crc
    cl.setCrcHigh(data[size-2]);
    cl.setCrcLow(data[size-1]);

    return cl;
}

