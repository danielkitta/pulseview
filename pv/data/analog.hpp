/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef PULSEVIEW_PV_DATA_ANALOG_HPP
#define PULSEVIEW_PV_DATA_ANALOG_HPP

#include "signaldata.hpp"

#include <deque>
#include <memory>

namespace pv {
namespace data {

class AnalogSegment;

class Analog : public SignalData
{
public:
	Analog();

	void push_segment(
		std::shared_ptr<AnalogSegment> &segment);

	const std::deque< std::shared_ptr<AnalogSegment> >&
		analog_segments() const;

	std::vector< std::shared_ptr<Segment> > segments() const;

	void clear();

	uint64_t max_sample_count() const;

private:
	std::deque< std::shared_ptr<AnalogSegment> > segments_;
};

} // namespace data
} // namespace pv

#endif // PULSEVIEW_PV_DATA_ANALOG_HPP
