#include "channel_view.h"
#include "ui_channel_view.h"

ChannelView::ChannelView(ChannelModel *model, QWidget *parent) :
    BaseView(parent),
    ui(new Ui::ChannelView),
    channelModel(model)
{
    ui->setupUi(this);
    initUI();
    initConnections();
    initData();
}

void ChannelView::initUI() {
    // 初始化UI组件
    ui->tableView->setModel(channelModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void ChannelView::initConnections() {
    // 初始化信号槽连接
    connect(ui->addButton, &QPushButton::clicked, this, &ChannelView::onAddButtonClicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &ChannelView::onRemoveButtonClicked);
}

void ChannelView::initData() {
    // 初始化数据
    channelModel->refresh();
}

void ChannelView::onAddButtonClicked() {
    // 处理添加按钮点击
    emit addChannelRequested();
}

void ChannelView::onRemoveButtonClicked() {
    // 处理删除按钮点击
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        emit removeChannelRequested(index.row());
    }
}