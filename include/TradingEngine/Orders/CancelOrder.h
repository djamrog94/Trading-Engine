/**
 *  @file   CancelOrder.h
 *  @brief  Cancel order header
 *  @author David
 *  @date   2021-15-10
 ***********************************************/

#pragma once
#include "TradingEngine/Orders/OrderCore.h"
#include "TradingEngine/Orders/ModifyOrder.h"
#include <string>

namespace TradingEngine::Orders {
	class CancelOrder : public OrderCore
	{
	public:
		CancelOrder(OrderCore& orderBase);
		OrderCore orderBase_;
	};
	std::ostream& operator << (std::ostream& outs, const CancelOrder& co);
}
