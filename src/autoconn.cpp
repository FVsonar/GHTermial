#include "autoconn.h"
#include <QObject>
#include <Serial/Manager.h>
#include "Dataproc.h"

using namespace Serial;

AutoConn::AutoConn(QObject *parent): QObject{parent}
{
    m_isConnecSuccess = false;
    m_count = 0;
    m_connstate = 0;
    // 间隔发送
    m_pTimer.setInterval(1000);
    m_pTimer.setTimerType(Qt::PreciseTimer);
    connect(&m_pTimer, &QTimer::timeout, this,&AutoConn::handleTimeout);

    // 间隔读取
    m_rTimer.setInterval(500);
    m_rTimer.setTimerType(Qt::PreciseTimer);
    connect(&m_rTimer, &QTimer::timeout, this, &AutoConn::checkDevice);
}

void AutoConn::startConnDevive()
{

    GetSerialPortNames();
    m_count = 0;
    m_connstate = 0;
    m_pTimer.start();
    qInfo() << "自动连接开始" ;


}


void  AutoConn::GetSerialPortNames(void)
{

  nameSerialPort = Manager::getInstance()->portList();
}


void AutoConn::handleTimeout(void)
{
      auto my_port = Manager::getInstance();
      auto my_data = DataProc::getInstance();
      static quint8 countBak = 0xff;
        GetSerialPortNames();
        if (!m_isConnecSuccess )
        {

            if(countBak != m_count && nameSerialPort.count()>0)
            {
                countBak = m_count;
                my_port->disconnectDevice();
                //m_count是已经连接的端口数，countport是总共的端口数
                if (m_count > nameSerialPort.count())
                {
                    m_count = 0;
                    m_pTimer.stop();
                    m_rTimer.stop();
                    m_connstate = 0x03; // 连接失败
                    countBak = 0xff;
                    qInfo() << m_count;
                     qInfo() << nameSerialPort.count() ;
                   //  qInfo() << "连接失败" ;
                   // ui->label_status->setText("未连接");
                  //  QMessageBox::critical(this, tr("Error"), "打开串口失败！");
                  //  ui->Btn_Reconnect->setEnabled(true);
                    return;
                }
               // ui->label_status->setText("正在连接...");
                //my_port->setPortName(nameSerialPort[m_count++]);
                if(nameSerialPort.at(m_count).contains("USB") || nameSerialPort.at(m_count).contains("Q900"))
                {
                    my_port->setPortIndex(m_count);
                    my_port->connectDevice();
                }
                else
                {
                 //   qInfo() << "错误的名字" ;
                    m_count++;
                }

                if (my_port->connected())
                {
                   // sendCommand(connectBuffer);
                    my_data->sendCheckDevice();
                    m_rTimer.start();
                }
                else
                {
                //    qInfo() << "无法打开" ;
                    m_count++;
                }
            }
        }
        else
        {

            m_pTimer.stop();
            m_rTimer.stop();

//             qInfo() << "已连接" ;
             m_connstate = 0x02; // 连接成功
              m_count = 0;
              countBak = 0xff;
        }


}


void AutoConn::checkDevice(void)
{
    static quint8 checkcount = 0;

    if(m_isConnecSuccess == false)
    {
         m_isConnecSuccess = DataProc::getInstance()->deviceVerify();
        checkcount ++;
        if(checkcount >= 10)
        {
            checkcount = 0;
            m_count++;
            m_rTimer.stop();
            qInfo() << "未收到回复" ;
        }
    }

}

quint8 AutoConn::getconnState(void)
{
    return  m_connstate;
}
