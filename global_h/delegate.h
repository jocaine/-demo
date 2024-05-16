#ifndef DELEGATE_H
#define DELEGATE_H
#include <QStyledItemDelegate>
#include<QListView>
#include<QStandardItem>
#include<QStandardItemModel>
#include<QApplication>
#include <QPainter>
#include <QPushButton>
class MyItemDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        // 设置项的高度为50，您可以根据需要调整高度
        size.setHeight(70);

        return size;
    }

    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override {
        QStyledItemDelegate::initStyleOption(option, index);
        QFont font("LiSu", 17, QFont::Normal); // 设置隶书字体样式
        option->font = font;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        // 获取项的文本
        QVariant displayData = index.data(Qt::DisplayRole);

        // 绘制项的背景
        painter->drawPixmap(option.rect,QPixmap("://res/moto.png"));// 白色背景
        // 绘制项的文本
        QStyledItemDelegate::paint(painter, option, index);
    }
};
class LinkItemDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(70); // 设置项的高度为 70
        return size;
    }

    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override {
        QStyledItemDelegate::initStyleOption(option, index);
        QFont font("LiSu", 17, QFont::Normal); // 设置隶书字体样式
        option->font = font;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        // 绘制项的背景
        painter->drawPixmap(option.rect, QPixmap("://res/moto.png")); // 白色背景

        // 绘制项的文本
        QStyledItemDelegate::paint(painter, option, index);

        // 添加按钮
        QPushButton deleteButton("Delete");
        QRect rect = option.rect;
        rect.setLeft(rect.right() - deleteButton.sizeHint().width() - 5); // 将按钮放置在项的最右侧
        deleteButton.setGeometry(rect);
        deleteButton.setStyleSheet("background-color: red; color: white;"); // 设置按钮的样式
        deleteButton.show();
    }
};

#endif // DELEGATE_H
