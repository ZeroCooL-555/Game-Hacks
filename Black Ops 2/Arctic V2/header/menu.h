#pragma once


struct Checks
{
	// ESP bools
	bool ESP;
	bool esp_border;
	bool esp_corner;
	bool Lines;
	bool Distance;
	

	// Misc bools
	bool vsat;
	
	bool player_fov;

	//Menu bool
	bool show_hide;
};

namespace menu
{
	void Toggles();
	void D3DMenu();
	void StartHack();
}

extern Checks checks;