/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamite <akamite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:37:02 by akamite           #+#    #+#             */
/*   Updated: 2024/09/12 23:41:39 by akamite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <iostream>

namespace irc
{
    class User
    {
    private:
        std::string nickname;

    public:
        User();
        ~User();
    };
}

#endif
