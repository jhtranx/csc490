/*****************************************************************************
 * Example code modified from Mapnik rundemo.cpp (r727, license LGPL).
 * Renders the State of California using USGS state boundaries data.
 *****************************************************************************/


#include <mapnik/map.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/rule.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/symbolizer.hpp>
#include <mapnik/text/placements/dummy.hpp>
#include <mapnik/text/text_properties.hpp>
#include <mapnik/text/formatting/text.hpp>
#include <mapnik/datasource_cache.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/agg_renderer.hpp>
#include <mapnik/expression.hpp>
#include <mapnik/color_factory.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/unicode.hpp>
#include <mapnik/save_map.hpp>
#include <mapnik/cairo_io.hpp>

#if defined(HAVE_CAIRO)
#include <mapnik/cairo/cairo_renderer.hpp>
#include <mapnik/cairo/cairo_image_util.hpp>
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "demogData.h"
#include "demogCombo.h"
#include "psData.h"
#include "psCombo.h"
#include "regionData.h"
#include "parse.h"
#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"

#include "states.h"
#include "CountyMap.h"

visitorCombineCounty DataProjSetUp() {
	
	vector<shared_ptr<regionData>> pileOfData;
	read_csv(pileOfData, "./demo/490-MapLab7-STARTER/county_demographics.csv", DEMOG);
	read_csv(pileOfData, "./demo/490-MapLab7-STARTER/fatal-police-shootings-data-Q.csv", POLICE);

	visitorCombineCounty county_report_ = visitorCombineCounty("./demo/490-MapLab7-STARTER/uscities.csv");

	for (const auto &obj : pileOfData) {
		obj->Accept(county_report_);
	}
	return county_report_;
}

std::vector<vector<string>> MakeBorderBinList(visitorCombineCounty county_report_) {
	
	std::map<string, shared_ptr<demogCombo>> demog_combo_map_ = county_report_.GetDemogComboMap();
	std::map<string, shared_ptr<psCombo>> ps_combo_map_ = county_report_.GetPoliceComboMap();
	std::vector<std::pair<string, shared_ptr<demogCombo>>> demog_combo_list_;

	for (auto itr = demog_combo_map_.begin(); itr != demog_combo_map_.end(); ++itr)
    	demog_combo_list_.push_back(*itr);

	vector<vector<string>> border_bins_list_;
	// red is at idx 0, black is at idx 1

	border_bins_list_.push_back(vector<string> {});
	border_bins_list_.push_back(vector<string> {});

	// FOR HIGH SCHOOL MENTAL ILLNESS
	for (auto &obj : demog_combo_list_) {
		double fatal_high_school_percent_ = 0.0;

		shared_ptr<psCombo> ps_combo_ = ps_combo_map_[obj.first];
		if (ps_combo_ != 0)
			fatal_high_school_percent_ = ps_combo_->GetNumMentalIllnessPercent();	

		if (fatal_high_school_percent_ > 0.50)
			border_bins_list_.at(0).push_back(obj.first);
		else
			border_bins_list_.at(1).push_back(obj.first);
	}

	// FOR ALL QUERIES BESIDES HIGH SCHOOL MENTAL ILLNESS
	// for (auto &obj : demog_combo_list_) {
	// 	double fatal_race_percent_ = 0.0;
	// 	double demog_race_percent_ = obj.second->GetNumMentalIllnessPercent();
	// 	shared_ptr<psCombo> ps_combo_ = ps_combo_map_[obj.first];
	// 	if (ps_combo_ != 0)
	// 		fatal_race_percent_ = ps_combo_->GetNumMentalIllnessPercent();	

	// 	if (fatal_race_percent_ > demog_race_percent_)
	// 		border_bins_list_.at(0).push_back(obj.first);
	// 	else
	// 		border_bins_list_.at(1).push_back(obj.first);
	// }
	return border_bins_list_;
}

std::vector<vector<string>> MakeFillBinList(visitorCombineCounty county_report_) {

	std::map<string, shared_ptr<demogCombo>> demog_combo_map_ = county_report_.GetDemogComboMap();
	std::map<string, shared_ptr<psCombo>> ps_combo_map_ = county_report_.GetPoliceComboMap();
	std::vector<std::pair<string, shared_ptr<demogCombo>>> demog_combo_list_;
	std::vector<string> county_key_list_;

	for (auto itr = demog_combo_map_.begin(); itr != demog_combo_map_.end(); ++itr)
    	demog_combo_list_.push_back(*itr);
	sort(demog_combo_list_.begin(), demog_combo_list_.end(), [=] 
		(std::pair<string, shared_ptr<demogCombo>>& lhs, std::pair<string, shared_ptr<demogCombo>>& rhs) {
    	return lhs.second->GetBachelorsDegPercentCombo() < rhs.second->GetBachelorsDegPercentCombo();
	});
	for (auto &obj : demog_combo_list_) {
		county_key_list_.push_back(obj.first);
	}
	vector<vector<string>> fill_bins_list_;
	// creating 8 vectors (bins) in binslist
	for (int j = 0; j < 8; j++) {
		fill_bins_list_.push_back(vector<string> {});
	}

	int bins_num_ = 8;
	int curr_bin_idx_ = 0;

	double max_data_percent_ = demog_combo_map_[county_key_list_[county_key_list_.size() - 1]]->GetBachelorsDegPercentCombo();
	double min_data_percent_ = demog_combo_map_[county_key_list_[0]]->GetBachelorsDegPercentCombo();
	double increment_ = (max_data_percent_ - min_data_percent_) / bins_num_;

	double curr_bin_max_value_ = increment_ + min_data_percent_;

	for (int i = 0; i < (county_key_list_.size() - 1); i++) {
		string curr_county_name_ =  county_key_list_.at(i);
		shared_ptr<demogCombo> curr_county_demog_combo_ = demog_combo_map_[curr_county_name_];
		double curr_county_percent_ = curr_county_demog_combo_->GetBachelorsDegPercentCombo();

		if (curr_county_percent_ > curr_bin_max_value_) {
			curr_bin_max_value_ += increment_;
			curr_bin_idx_ += 1;
		}
		fill_bins_list_[curr_bin_idx_].push_back(curr_county_name_);
	}
		
	return fill_bins_list_;
}

using namespace mapnik;
std::vector<string> CreateExpressions(vector<vector<string>> bins_list_, vector<color> color_map_) {
	CountyMap theCountyMap("demo/data/uscities.csv");

	std::vector<string> expr_list_;
	int state_code_;
	int county_code_;
	int bin_idx_ = 0;

	for (int j=0; j < color_map_.size(); j++) {
		expr_list_.push_back("([STATEFP] = \'");
	}

	for (auto bin_ : bins_list_) {
		for (int i = 0; i < bin_.size(); i++) {
			string county_name_ = bin_[i];
			assert(theCountyMap.keyToCounty[county_name_].count() > 0);
			countyID county_id_object_ = theCountyMap.keyToCounty[county_name_];
			state_code_ = county_id_object_.countyfips / 1000;
			
			if (state_code_ < 10)
				expr_list_[bin_idx_] += "0" + to_string(state_code_)+"\'";
			else
				expr_list_[bin_idx_] += to_string(state_code_)+"\'";
			// this sets countyCode to the expr
			county_code_ = county_id_object_.countyfips % 1000;
			if (county_code_ < 10)
				expr_list_[bin_idx_] += " and [COUNTYFP] = \'00" + to_string(county_code_)+"\')";
			else if (county_code_ < 100)
				expr_list_[bin_idx_] += " and [COUNTYFP] = \'0" + to_string(county_code_)+"\')";
			else
				expr_list_[bin_idx_] += " and [COUNTYFP] = \'" + to_string(county_code_)+"\')";
			if (i != (bin_.size() - 1))
				expr_list_[bin_idx_] += " or ([STATEFP] = \'";
		}

		bin_idx_ += 1;
	}
	return expr_list_;

}


int main ( int argc , char** argv)
{

	using namespace mapnik;
	visitorCombineCounty county_report_ = DataProjSetUp();
	std::vector<vector<string>> fill_bins_list_ = MakeFillBinList(county_report_);
	std::vector<vector<string>> border_bins_list_ = MakeBorderBinList(county_report_);

	std::vector<color> fill_color_map_ = {color(235, 91, 101),
	color(245, 134, 91),
	color(223, 170, 94),
	color(245, 213, 91),
	color(235, 235, 75),
	color(128, 235, 96),
	color(95, 245, 155),
	color(91, 80, 235) };

	std::vector<color> border_color_map_ = {color(255, 0, 0),
	color(0, 0, 0) };

	const std::string srs_lcc="+proj=lcc +ellps=GRS80 +lat_0=49 +lon_0=-95 +lat+1=49 +lat_2=77 +datum=NAD83 +units=m +no_defs";
	const std::string srs_merc="+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0.0 +k=1.0 +units=m +nadgrids=@null +wktext +no_defs +over";

	try {
		std::cout << " creating partial US map... \n";
		datasource_cache::instance().register_datasources("plugins/input/");
		freetype_engine::register_font("/fonts/dejavu-ttf-2.14/DejaVuSans.ttf");

		Map m(1200,800);
		m.set_background(parse_color("cadetblue"));
		//set projection
		m.set_srs(srs_merc);

		// create styles
		std::cout << "creating expression rules" << std::endl;

		std::vector<string> fill_expr_list_ = CreateExpressions(fill_bins_list_, fill_color_map_);

		for (int k = 0; k < fill_color_map_.size(); k++) {
			feature_type_style section_style;
			{
			rule section_rule;
			section_rule.set_filter(parse_expression(fill_expr_list_[k])); 
			{
					polygon_symbolizer poly_sym;
					put(poly_sym, keys::fill, fill_color_map_.at((fill_color_map_.size()-1)-k));
					section_rule.append(std::move(poly_sym));
			}
			section_style.add_rule(std::move(section_rule));
			}
			m.insert_style("section"+to_string(k), std::move(section_style));
			cout << "INSERTED LAYERS: " << "section"+to_string(k) << endl;
		}
		
		//START OF BORDERLINE CODE

		std::vector<string> border_expr_list_ = CreateExpressions(border_bins_list_, border_color_map_);;

		for (int p = 0; p < border_color_map_.size(); p++) {
			feature_type_style section_style;
			{
			rule section_rule;
			section_rule.set_filter(parse_expression(border_expr_list_[p])); 
			{
				line_symbolizer line_sym;
				put(line_sym,keys::stroke, border_color_map_.at(p));
				put(line_sym,keys::stroke_width,0.5);
				put(line_sym,keys::stroke_linecap,ROUND_CAP);
				put(line_sym,keys::stroke_linejoin,ROUND_JOIN);
				section_rule.append(std::move(line_sym));
			}
			section_style.add_rule(std::move(section_rule));
			}
			m.insert_style("border_section"+to_string(p), std::move(section_style));
			cout << "INSERTED BORDER: " << "border_section"+to_string(p) << endl;
		}

		// Layers
		// state data
		{
			parameters p;
			p["type"]="shape";
			p["file"]="demo/data/cb_2018_us_county_20m";
			p["encoding"]="utf8";

			layer lyr("DataProjMap");
			lyr.set_datasource(datasource_cache::instance().create(p));
			for (int l = 0; l < fill_color_map_.size(); l++) {
				lyr.add_style("section"+to_string(l));
			}
			lyr.set_srs(srs_lcc);
	
			m.add_layer(lyr);
		}

		//county boundaries
		{
			parameters p;
			p["type"]="shape";
			p["file"]="demo/data/cb_2018_us_county_20m";
			p["encoding"]="utf8";

			layer lyr("StateLines");
			lyr.set_datasource(datasource_cache::instance().create(p));
			lyr.add_style("border_section0");
			lyr.add_style("border_section1");
			lyr.set_srs(srs_lcc);
	
			m.add_layer(lyr);
		}

		std::cout << "made layers" << std::endl;
		

		m.zoom_all();
		m.zoom(0.3);
		m.pan(-700, 400);

		image_rgba8 buf(m.width(),m.height());
		agg_renderer<image_rgba8> ren(m,buf);
		ren.apply();
		std::string msg("Writing out data for warm to cool coloring based on police shooting data:\n");
#ifdef HAVE_JPEG
		save_to_file(buf,"USMapPS.jpg","jpeg");
		msg += "- USMap.jpg\n";
#endif
					// save map definition (data + style)
		save_map(m, "map.xml");
	}
	catch ( std::exception const& ex )
	{
		std::cerr << "### std::exception: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch ( ... )
	{
		std::cerr << "### Unknown exception." << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

