% /* 
%  * Copyright (c) 2012-2013, Vuk Marojevic <marojevic@tsc.upc.edu>.
%  * This file is part of ALOE++ (http://flexnets.upc.edu/)
%  * 
%  * ALOE++ is free software: you can redistribute it and/or modify
%  * it under the terms of the GNU Lesser General Public License as published by
%  * the Free Software Foundation, either version 3 of the License, or
%  * (at your option) any later version.
%  * 
%  * ALOE++ is distributed in the hope that it will be useful,
%  * but WITHOUT ANY WARRANTY; without even the implied warranty o
%  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%  * GNU Lesser General Public License for more details.
%  * 
%  * You should have received a copy of the GNU Lesser General Public License
%  * along with ALOE++.  If not, see <http://www.gnu.org/licenses/>.
%  */

% Physical Uplink Control Channel (PUCCH) modulation

% Reference: 3GPP TS 136 211, V 10.5.0, Section 5.4


function out = pucch_modulation(in, format, direction)

    if (format == 0)
        out = pucch_mod1a(in, direction);
    elseif (format == 1)
        out = pucch_mod1b(in, direction);
    elseif ((format >= 2) && (format <= 5))
        out = pucch_mod2(in, direction);
    else
        fprintf('\nWrong format %d', format);
        out = {};
        return;
    end

end