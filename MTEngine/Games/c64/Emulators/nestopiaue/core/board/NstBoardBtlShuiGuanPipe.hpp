////////////////////////////////////////////////////////////////////////////////////////
//
// Nestopia - NES/Famicom emulator written in C++
//
// Copyright (C) 2003-2008 Martin Freij
//
// This file is part of Nestopia.
//
// Nestopia is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// Nestopia is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Nestopia; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef NST_BOARD_BTL_SHUIGUANPIPE_H
#define NST_BOARD_BTL_SHUIGUANPIPE_H

#ifdef NST_PRAGMA_ONCE
#pragma once
#endif

namespace Nes
{
	namespace Core
	{
		namespace Boards
		{
			namespace Btl
			{
				class ShuiGuanPipe : public Board
				{
				public:

					explicit ShuiGuanPipe(const Context&);

				private:

					void SubReset(bool);
					void SubSave(State::Saver&) const;
					void SubLoad(State::Loader&,dword);
					void UpdateChr(uint,uint) const;
					void Sync(Event,Input::Controllers*);

					NES_DECL_PEEK( 6000 );
					NES_DECL_POKE( B000 );
					NES_DECL_POKE( F000 );
					NES_DECL_POKE( F004 );
					NES_DECL_POKE( F008 );
					NES_DECL_POKE( F00C );

					struct Irq
					{
						void Reset(bool);
						bool Clock();

						ibool enabled;
						uint count[2];
					};

					Timer::M2<Irq> irq;
				};
			}
		}
	}
}

#endif
