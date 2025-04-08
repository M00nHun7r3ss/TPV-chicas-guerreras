#include "MiraculousComponent.h"

void MiraculousComponent::init()
{
	_N = _rand.nextInt(1, 6); //cambiar por 10 y 21
	_M = _rand.nextInt(1, 6);
}

void MiraculousComponent::update()
{
	VirtualTimer& vt = sdlutils().virtualTimer();
	Uint32 _timeBetweenEachSpawn;

	// Si no es milagroso...
	if (!_isMiraculous)
	{
		// --- TIEMPO DURANTE NO MILAGROSO ---
		//La fruta será normal un N random entre 10 y 20 s
		_N = _rand.nextInt(1, 6); //cambiar por 10 y 21
		_timeBetweenEachSpawn = _N * 1000;

		//Pasado ese tiempo
		if (vt.currTime() > _timeBetweenEachSpawn + _lastFruitChanged) {
			//La fruta vuelve a ser milagrosa
			_isMiraculous = true;
			_lastFruitChanged = vt.currTime();
		}
		// -o-o-o-o-o-
	}
	else // cuando es milagroso...
	{

		// --- TIEMPO DURANTE MILAGROSO ---
		//La fruta será milagrosa un M random entre 1 y 5 s
		_M = _rand.nextInt(1, 6);
		_timeBetweenEachSpawn = _M * 1000;

		//Pasado ese tiempo
		if (vt.currTime() > _timeBetweenEachSpawn + _lastFruitChanged) {
			//La fruta vuelve a ser normal
			_isMiraculous = false;
			_lastFruitChanged = vt.currTime();
		}
		// -o-o-o-o-o-
	}

	
		
	
}
