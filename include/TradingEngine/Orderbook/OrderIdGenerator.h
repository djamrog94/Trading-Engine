#pragma once
#include <boost/date_time.hpp>
namespace TradingEngine::Orderbook
{
	class OrderIdGenerator
	{
	public:
		static OrderIdGenerator& Instance();
		OrderIdGenerator(OrderIdGenerator const&) = delete;             
		OrderIdGenerator(OrderIdGenerator&&) = delete;                  
		OrderIdGenerator& operator=(OrderIdGenerator const&) = delete;  
		OrderIdGenerator& operator=(OrderIdGenerator&&) = delete;

		static long generateOrderId();

	protected:
		OrderIdGenerator();


	};

}

