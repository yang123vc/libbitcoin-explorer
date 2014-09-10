/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BX_INPUT_VALIDATE_HPP
#define BX_INPUT_VALIDATE_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <explorer/command.hpp>
#include <explorer/define.hpp>
#include <explorer/generated.hpp>
#include <explorer/primitives/address.hpp>
#include <explorer/primitives/base16.hpp>
#include <explorer/primitives/base58.hpp>
#include <explorer/primitives/btc.hpp>
#include <explorer/primitives/btc160.hpp>
#include <explorer/primitives/btc256.hpp>
#include <explorer/primitives/ec_private.hpp>
#include <explorer/primitives/ec_public.hpp>
#include <explorer/primitives/encoding.hpp>
#include <explorer/primitives/hashtype.hpp>
#include <explorer/primitives/hd_key.hpp>
#include <explorer/primitives/hd_priv.hpp>
#include <explorer/primitives/hd_pub.hpp>
#include <explorer/primitives/header.hpp>
#include <explorer/primitives/input.hpp>
#include <explorer/primitives/output.hpp>
#include <explorer/primitives/prefix.hpp>
#include <explorer/primitives/raw.hpp>
#include <explorer/primitives/script.hpp>
#include <explorer/primitives/stealth.hpp>
#include <explorer/primitives/transaction.hpp>
#include <explorer/primitives/wif.hpp>
#include <explorer/primitives/wrapper.hpp>
#include <explorer/utility/compat.hpp>
#include <explorer/utility/config.hpp>
#include <explorer/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_INPUT_VALIDATE_INDEX_OUT_OF_RANGE \
    "The index does not refer to an existing input."
#define BX_INPUT_VALIDATE_INDEX_VALID_SIGNATURE \
    "The signature is valid."
#define BX_INPUT_VALIDATE_INDEX_INVALID_SIGNATURE \
    "The signature is not valid."

/**
 * Class to implement the input-validate command.
 */
class input_validate 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "input-validate"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return input_validate::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "TRANSACTION";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("TRANSACTION", 1)
            .add("EC_PUBLIC_KEY", 1)
            .add("SCRIPT_CODE", 1)
            .add("SIGNATURE", 1);
    }
	
	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
        //load_path(get_transaction_argument(), "TRANSACTION", variables);
    }
    
    /**
     * Load program option definitions.
     * The implicit_value call allows flags to be strongly-typed on read while
     * allowing but not requiring a value on the command line for the option.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    virtual options_metadata& load_options()
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
            (
                BX_VARIABLE_CONFIG ",c",
                value<boost::filesystem::path>(),                 
                "The path and file name for the configuration settings file for this application."
            )
            (
                "help,h",
                value<bool>(&option_.help)->implicit_value(true),
                "Validate the a transaction input signature."
            )
            (
                "index,i",
                value<size_t>(&option_.index),
                "The ordinal position of the input within the transaction, defaults to zero."
            )
            (
                "sighash,s",
                value<primitives::hashtype>(&option_.sighash),
                "A token that indicates how the transaction should be signed. Options are 'all', 'none', 'single', or 'anyone_can_pay', defaults to 'single'."
            )
            (
                "TRANSACTION",
                value<std::string>()->required(),
                "The file path of the Base16 transaction."
            )
            (
                "EC_PUBLIC_KEY",
                value<primitives::ec_public>(&argument_.ec_public_key)->required(),
                "The Base16 EC public key to verify against."
            )
            (
                "SCRIPT_CODE",
                value<primitives::script>(&argument_.script_code)->required(),
                "The Base16 ... script ..."
            )
            (
                "SIGNATURE",
                value<primitives::base16>(&argument_.signature),
                "The Base16 signature to validate. If not specified the signature is read from STDIN."
            );

        return options;
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual console_result invoke(std::ostream& output, std::ostream& cerr);
        
    /* Properties */

    /**
     * Get the value of the TRANSACTION argument.
     */
    virtual primitives::transaction& get_transaction_argument()
    {
        return argument_.transaction;
    }
    
    /**
     * Set the value of the TRANSACTION argument.
     */
    virtual void set_transaction_argument(
        const primitives::transaction& value)
    {
        argument_.transaction = value;
    }

    /**
     * Get the value of the EC_PUBLIC_KEY argument.
     */
    virtual primitives::ec_public& get_ec_public_key_argument()
    {
        return argument_.ec_public_key;
    }
    
    /**
     * Set the value of the EC_PUBLIC_KEY argument.
     */
    virtual void set_ec_public_key_argument(
        const primitives::ec_public& value)
    {
        argument_.ec_public_key = value;
    }

    /**
     * Get the value of the SCRIPT_CODE argument.
     */
    virtual primitives::script& get_script_code_argument()
    {
        return argument_.script_code;
    }
    
    /**
     * Set the value of the SCRIPT_CODE argument.
     */
    virtual void set_script_code_argument(
        const primitives::script& value)
    {
        argument_.script_code = value;
    }

    /**
     * Get the value of the SIGNATURE argument.
     */
    virtual primitives::base16& get_signature_argument()
    {
        return argument_.signature;
    }
    
    /**
     * Set the value of the SIGNATURE argument.
     */
    virtual void set_signature_argument(
        const primitives::base16& value)
    {
        argument_.signature = value;
    }

    /**
     * Get the value of the help option.
     */
    virtual bool& get_help_option()
    {
        return option_.help;
    }
    
    /**
     * Set the value of the help option.
     */
    virtual void set_help_option(
        const bool& value)
    {
        option_.help = value;
    }

    /**
     * Get the value of the index option.
     */
    virtual size_t& get_index_option()
    {
        return option_.index;
    }
    
    /**
     * Set the value of the index option.
     */
    virtual void set_index_option(
        const size_t& value)
    {
        option_.index = value;
    }

    /**
     * Get the value of the sighash option.
     */
    virtual primitives::hashtype& get_sighash_option()
    {
        return option_.sighash;
    }
    
    /**
     * Set the value of the sighash option.
     */
    virtual void set_sighash_option(
        const primitives::hashtype& value)
    {
        option_.sighash = value;
    }

private:

    /**
     * Command line argument bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct argument
    {
        argument()
          : transaction(),
            ec_public_key(),
            script_code(),
            signature()
        {
        }
        
        primitives::transaction transaction;
        primitives::ec_public ec_public_key;
        primitives::script script_code;
        primitives::base16 signature;
    } argument_;
    
    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : help(),
            index(),
            sighash()
        {
        }
        
        bool help;
        size_t index;
        primitives::hashtype sighash;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif