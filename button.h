#ifndef BUTTON_H
#define BUTTON_H
#include<QToolButton>

class Button : public QToolButton
{
    Q_OBJECT
private:
    QIcon m_NormalIcon;
    QIcon m_FocusIcon;
    QIcon m_PressedIcon;
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    Button(QWidget *parent = 0);
    virtual ~Button();
    void SetButtonIcons(const QIcon &normal,
                        const QIcon &focus = QIcon(),
                        const QIcon &pressed = QIcon()
    );
    void setFlat();
};

#endif // BUTTON_H
