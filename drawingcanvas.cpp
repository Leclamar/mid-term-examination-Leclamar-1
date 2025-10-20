#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    /* Todo
     * Implement lines drawing per even pair
    */

    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection() {
    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "image width: " << image.width() << endl;
    cout << "image height: " << image.height() << endl;

    // To not crash we set initial size of the matrix
    vector<CustomMatrix> windows(image.width() * image.height());

    int windowCount = 0;

    // ------------------------
    // 3x3 Window Detection
    // ------------------------
    const int WINDOW_SIZE3x3 = 3;
    const int HALF_SIZE3x3 = WINDOW_SIZE3x3 / 2;  // = 1

    for (int i = HALF_SIZE3x3; i < image.width() - HALF_SIZE3x3; i++) {
        for (int j = HALF_SIZE3x3; j < image.height() - HALF_SIZE3x3; j++) {
            bool local_window[WINDOW_SIZE3x3][WINDOW_SIZE3x3] = {false};
            bool hasNonWhitePixel = false;

            for (int m = -HALF_SIZE3x3; m <= HALF_SIZE3x3; m++) {
                for (int n = -HALF_SIZE3x3; n <= HALF_SIZE3x3; n++) {
                    QRgb rgbValue = image.pixel(i + m, j + n);

                    int red = qRed(rgbValue);
                    int green = qGreen(rgbValue);
                    int blue = qBlue(rgbValue);
                    bool isDrawn = (red < 240 || green < 240 || blue < 240);

                    local_window[m + HALF_SIZE3x3][n + HALF_SIZE3x3] = isDrawn;
                    if (isDrawn) hasNonWhitePixel = true;
                }
            }

            if (hasNonWhitePixel) {
                windowCount++;
                cout << "\n- [3x3] Window #" << windowCount
                     << " at position (" << i << ", " << j << ") -" << endl;

                for (int row = 0; row < WINDOW_SIZE3x3; row++) {
                    for (int col = 0; col < WINDOW_SIZE3x3; col++) {
                        cout << (local_window[row][col] ? "1" : "0") << " ";
                    }
                    cout << endl;
                }
            }
        }
    }

    // ------------------------
    // 5x5 Window Detection
    // ------------------------
    const int WINDOW_SIZE5x5 = 5;
    const int HALF_SIZE5x5 = WINDOW_SIZE5x5 / 2;  // = 2

    for (int i = HALF_SIZE5x5; i < image.width() - HALF_SIZE5x5; i++) {
        for (int j = HALF_SIZE5x5; j < image.height() - HALF_SIZE5x5; j++) {
            bool local_window[WINDOW_SIZE5x5][WINDOW_SIZE5x5] = {false};
            bool hasNonWhitePixel = false;

            for (int m = -HALF_SIZE5x5; m <= HALF_SIZE5x5; m++) {
                for (int n = -HALF_SIZE5x5; n <= HALF_SIZE5x5; n++) {
                    QRgb rgbValue = image.pixel(i + m, j + n);

                    int red = qRed(rgbValue);
                    int green = qGreen(rgbValue);
                    int blue = qBlue(rgbValue);
                    bool isDrawn = (red < 240 || green < 240 || blue < 240);

                    local_window[m + HALF_SIZE5x5][n + HALF_SIZE5x5] = isDrawn;
                    if (isDrawn) hasNonWhitePixel = true;
                }
            }

            if (hasNonWhitePixel) {
                windowCount++;
                cout << "\n- [5x5] Window #" << windowCount
                     << " at position (" << i << ", " << j << ") -" << endl;

                for (int row = 0; row < WINDOW_SIZE5x5; row++) {
                    for (int col = 0; col < WINDOW_SIZE5x5; col++) {
                        cout << (local_window[row][col] ? "1" : "0") << " ";
                    }
                    cout << endl;
                }
            }
        }
    }

    cout << "\nTotal non-empty windows found (3x3 + 5x5): " << windowCount << endl;
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4); // 4-pixel wide line
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        // Set the painter's pen to our custom pen.
        painter.setPen(pen);

        for(int i=0;i<m_points.size()-1;i+=2){
            //cout << m_points[i].x() << endl;
            painter.drawLine(m_points[i], m_points[i+1]);
        }
        isPaintLinesClicked = false;

        //return painter pen to blue
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}


