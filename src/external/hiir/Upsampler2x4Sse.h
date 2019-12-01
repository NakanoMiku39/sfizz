/*****************************************************************************

        Upsampler2x4Sse.h
        Author: Laurent de Soras, 2015

Upsamples vectors of 4 float by a factor 2 the input signal, using the SSE
instruction set.

This object must be aligned on a 16-byte boundary!

Template parameters:
	- NC: number of coefficients, > 0

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (hiir_Upsampler2x4Sse_HEADER_INCLUDED)
#define hiir_Upsampler2x4Sse_HEADER_INCLUDED

#if defined (_MSC_VER)
	#pragma warning (4 : 4250)
#endif



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "hiir/def.h"
#include "hiir/StageDataSse.h"

#include <xmmintrin.h>

#include <array>



namespace hiir
{



template <int NC>
class Upsampler2x4Sse
{

	static_assert ((NC > 0), "Number of coefficient must be positive.");

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	enum {         NBR_COEFS = NC };

	               Upsampler2x4Sse ();

	void				set_coefs (const double coef_arr [NBR_COEFS]);
	hiir_FORCEINLINE void
	               process_sample (__m128 &out_0, __m128 &out_1, __m128 input);
	void				process_block (float out_ptr [], const float in_ptr [], long nbr_spl);
	void				clear_buffers ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	typedef std::array <StageDataSse, NBR_COEFS + 2> Filter;   // Stages 0 and 1 contain only input memories

	Filter         _filter; // Should be the first member (thus easier to align)



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	bool           operator == (const Upsampler2x4Sse <NC> &other) const;
	bool           operator != (const Upsampler2x4Sse <NC> &other) const;

}; // class Upsampler2x4Sse



}  // namespace hiir



#include "hiir/Upsampler2x4Sse.hpp"



#endif   // hiir_Upsampler2x4Sse_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
