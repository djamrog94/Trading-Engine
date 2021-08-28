#pragma once
#include "TradingEngine/Orders/OrderCore.h"
#include "TradingEngine/Orders/ModifyOrder.h"
#include <string>

namespace TradingEngine::Orders {
	class CancelOrder : public OrderCore
	{
	public:
		CancelOrder(OrderCore& orderBase);

		CancelOrder(ModifyOrder& modifyOrder);

	private:
		OrderCore orderBase_;
	};
}
