/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "data/data_statistics.h"
#include "statistics/chart_horizontal_lines_data.h"
#include "statistics/statistics_common.h"
#include "ui/effects/animations.h"
#include "ui/rp_widget.h"

namespace Statistic {

class ChartWidget : public Ui::RpWidget {
public:
	ChartWidget(not_null<Ui::RpWidget*> parent);

	void setChartData(Data::StatisticalChart chartData);
	void setHeightLimits(Limits newHeight, bool animated);

protected:
	void paintEvent(QPaintEvent *e) override;

private:
	void measureHeightThreshold();
	class Footer;

	std::unique_ptr<Footer> _footer;
	Data::StatisticalChart _chartData;

	bool _useMinHeight = false;

	Limits _currentHeight;
	Limits _animateToHeight;
	Limits _thresholdHeight = { -1, 0 };
	Limits _startFrom;
	Limits _startFromH;

	Limits _xPercentageLimits;
	struct {
		Limits was;
		Limits now;
		Ui::Animations::Basic animation;
		crl::time lastUserInteracted = 0;
		float64 progress = 0.;
	} _xPercentage;

	float64 _minMaxUpdateStep = 0.;

	crl::time _lastHeightLimitsChanged = 0;

	std::vector<ChartHorizontalLinesData> _horizontalLines;

	Ui::Animations::Simple _heightLimitsAnimation;

};

} // namespace Statistic
