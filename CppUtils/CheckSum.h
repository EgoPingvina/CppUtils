#pragma once

namespace CheckSum
{
	template<class U>
	inline uint16_t XOR(U& buffer, uint16_t start, uint16_t count)
	{
		uint16_t crc = 0x00;

		for (auto index = start; index < start + count; ++index)
			crc ^= buffer(index);

		return crc;
	}
}