/**
 *  @file   CancelOrder.cpp
 *  @brief  Cancel order object
 *  @author David
 *  @date   2021-15-10
 ***********************************************/

#include "TradingEngine/Orders/CancelOrder.h"
namespace TradingEngine::Orders {
	/*! \brief CancelOrder constructor.
	*/
	CancelOrder::CancelOrder(OrderCore& orderBase) : OrderCore(orderBase.getOrderId(), orderBase.getUsername(), orderBase.getSecurityId()), orderBase_(orderBase) {}

	/*! \brief Returns reference to ostream containing string representation of CancelOrder object.
	*/
	std::ostream& operator<<(std::ostream& outs, const CancelOrder& co)
	{
		return outs << co.orderBase_ << std::endl;
	}
	
}
