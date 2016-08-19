/**
 * Simple font inspector to check out monospace
 * font metrics
 *
 * Usage: testfont <Font Family>
 */
#include <QApplication>
#include <QTextStream>
#include <QFont>
#include <QFontInfo>
#include <QFontMetrics>
#include <QFontDatabase>
#include <QWidget>
#include <QPainter>

QTextStream& qStdOut()
{
	static QTextStream ts(stdout);
	return ts;
}

class FontTestWidget: public QWidget {
public:
	FontTestWidget(QFont f)
		:QWidget() {
		setFont(f);
	}

	virtual QSize sizeHint() const Q_DECL_OVERRIDE {
		QSize s;
		s.setHeight(fontMetrics().height()*2);
		s.setWidth(qMax(fontMetrics().boundingRect('T').width(),
					fontMetrics().width('T'))*2);
		return s;
	}

protected:
	virtual void paintEvent(QPaintEvent *ev) Q_DECL_OVERRIDE {
		QPainter p(this);

		QRect br;
		QFontMetrics fm = fontMetrics();
		br.setSize(QSize(fm.boundingRect('T').width(),
			fm.height()));

		QRect inner = br;
		inner.setWidth(fm.width('T'));
		inner.moveTop(height()/3);

		QRect max = inner;
		max.setWidth(fm.maxWidth());
		max.moveTop(height()/2);

		p.fillRect(max, Qt::red);
		p.fillRect(br, Qt::gray);
		p.fillRect(inner, Qt::darkGray);

		QPoint pos = br.bottomLeft();
		pos.setY(fm.ascent());
		p.drawText(pos, "T");
	}
};

void printFontInfo(const QFont& f)
{
	QFontInfo info(f);
	qStdOut() << "Font family: " << f.family() << endl;
	qStdOut() << "Exact match: " << info.exactMatch() << endl;
	qStdOut() << "Real family: " << info.family() << endl;
}

void printFontMetrics(const QFont& f)
{
	QFontMetrics fm(f);
	QFont fi(f);
	fi.setItalic(true);
	QFontMetrics fm_italic(fi);
	QFont fb(f);
	fb.setBold(true);
	QFontMetrics fm_bold(fb);
	QFont fbi(fb);
	fbi.setItalic(true);
	QFontMetrics fm_boldit(fbi);

	// Regular
	char err = (fm.averageCharWidth() != fm.maxWidth() ||
			fm.width("MM") != fm.maxWidth()*2) ? '!' : ' ';
	qStdOut() << err;
	qStdOut() << "  (Regular) Average char width: " << fm.averageCharWidth();
	qStdOut() << " Max char width: " << fm.maxWidth();
	qStdOut() << " Width(MM): " << fm.width("MM") << endl;
	qStdOut() << "             ";
	qStdOut() << "RectWidth(M): " << fm.boundingRect("M").width();
	qStdOut() << " Bearing: " << fm.leftBearing('M') << "/" << fm.rightBearing('M') << endl;

	// Italic
	err = (fm_italic.averageCharWidth() != fm_italic.maxWidth() ||
			fm_italic.width("MM") != fm_italic.maxWidth()*2 ||
			fm_italic.maxWidth() != fm.maxWidth()) ? '!' : ' ';
	qStdOut() << err;
	qStdOut() << "   (Italic) Average char width: " << fm_italic.averageCharWidth();
	qStdOut() << " Max char width: " << fm_italic.maxWidth();
	qStdOut() << " Width(MM): " << fm_italic.width("MM") << endl;
	qStdOut() << "             ";
	qStdOut() << "RectWidth(M): " << fm_italic.boundingRect("M").width();
	qStdOut() << " Bearing: " << fm_italic.leftBearing('M') << "/" << fm_italic.rightBearing('M') << endl;

	// Bold
	err = (fm_bold.averageCharWidth() != fm_bold.maxWidth() ||
			fm_bold.width("MM") != fm_bold.maxWidth()*2 ||
			fm_bold.maxWidth() != fm.maxWidth()) ? '!' : ' ';
	qStdOut() << err;
	qStdOut() << "     (Bold) Average char width: " << fm_bold.averageCharWidth();
	qStdOut() << " Max char width: " << fm_bold.maxWidth();
	qStdOut() << " Width(MM): " << fm_bold.width("MM") << endl;
	qStdOut() << "             ";
	qStdOut() << "RectWidth(M): " << fm_bold.boundingRect("M").width();
	qStdOut() << " Bearing: " << fm_bold.leftBearing('M') << "/" << fm_bold.rightBearing('M') << endl;

	// BoldItalic
	err = (fm_boldit.averageCharWidth() != fm_boldit.maxWidth() ||
			fm_boldit.width("MM") != fm_boldit.maxWidth()*2 ||
			fm_boldit.maxWidth() != fm.maxWidth()) ? '!' : ' ';
	qStdOut() << err;
	qStdOut() << "  (Bold+It) Average char width: " << fm_boldit.averageCharWidth();
	qStdOut() << " Max char width: " << fm_boldit.maxWidth();
	qStdOut() << " Width(MM): " << fm_boldit.width("MM") << endl;
	qStdOut() << "             ";
	qStdOut() << "RectWidth(M): " << fm_boldit.boundingRect("M").width();
	qStdOut() << " Bearing: " << fm_boldit.leftBearing('M') << "/" << fm_boldit.rightBearing('M') << endl;
}

void printFontList()
{
	QFontDatabase db;
    foreach (const QString &family, db.families()) {
		qStdOut() << family << "\n";
        foreach (const QString &style, db.styles(family)) {
			qStdOut() << "\t" << style << "\n";
		}
	}
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	if (app.arguments().size() < 2) {
		qStdOut() << "Usage: fontinfo <family>\n";
		qStdOut() << "       fontinfo -list";
		return -1;
	}

	if (app.arguments().at(1) == "-list") {
		printFontList();
		return 0;
	}

	QFont f;
	f.setStyleHint(QFont::TypeWriter, QFont::StyleStrategy(QFont::PreferDefault | QFont::ForceIntegerMetrics));
	f.setFamily(QStringList(app.arguments().mid(1)).join(" "));
	f.setFixedPitch(true);
	f.setKerning(false);

	printFontInfo(f);
	for (int i=10; i<=18; i++) {
		qStdOut() << "Font size: " << i << endl;
		f.setPointSize(i);
		printFontMetrics(f);
	}
	for (int i=24; i<=26; i++) {
		qStdOut() << "Font size: " << i << endl;
		f.setPointSize(i);
		printFontMetrics(f);
	}

	qStdOut() << "Font size: " << 64 << endl;
	f.setPointSize(64);
	printFontMetrics(f);

	// Save fontinfo.jpg
	f.setPointSize(64);
	f.setItalic(true);
	FontTestWidget w(f);
	w.repaint(w.rect());
	QPixmap p(w.sizeHint());
	w.render(&p);
	p.save("fontinfo.jpg");
	return 0;
}
