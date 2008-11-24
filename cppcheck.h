/*
 * c++check - c/c++ syntax checking
 * Copyright (C) 2007-2008 Daniel Marjamäki and Reijo Tomperi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 */

#ifndef CPPCHECK_H
#define CPPCHECK_H

#include <string>
#include <list>
#include <sstream>
#include <vector>
#include "settings.h"
#include "errorlogger.h"
#include "CheckFunctionUsage.h"

/**
 * This is the base class which will use other classes to do
 * static code analysis for C and C++ code to find possible
 * errors or places that could be improved.
 * Usage: See check() for more info.
 */
class CppCheck : public ErrorLogger
{
    public:
        /**
         * Constructor.
         */
        CppCheck( ErrorLogger &errorLogger );

        /**
         * Destructor.
         */
        virtual ~CppCheck();

        /**
         * This starts the actual checking. Note that you must call
         * parseFromArgs() or settings() and addFile() before calling this.
         */
        void check();

        /**
         * Adjust the settings before doing the check. E.g. show only
         * actual bugs or also coding style issues.
         *
         * @param settings New settings which will overwrite the old.
         */
        void settings( const Settings &settings );

        /**
         * Add new file to be checked.
         *
         * @param path Relative or absolute path to the file to be checked,
         * e.g. "cppcheck.cpp". Note that only source files (.c, .cc or .cpp)
         * should be added to the list. Include filese are gathered automatically.
         */
        void addFile( const std::string &path );

        /**
         * Parse command line args and get settings and file lists
         * from there.
         *
         * @param argc argc from main()
         * @param argv argv from main()
         * @return Empty string if parameters were accepted, or
         * string containing "help" text if no files were found to be
         * checked.
         */
        std::string parseFromArgs( int argc, char* argv[] );

    private:
        void checkFile(const std::string &code, const char FileName[]);
        virtual void reportErr( const std::string &errmsg);
        //void reportErr( const TOKEN *token, const std::string &errmsg);
        virtual void reportOut( const std::string &outmsg);

        std::list<std::string> _errorList;
        std::ostringstream _errout;
        Settings _settings;
        std::vector<std::string> _filenames;
        CheckFunctionUsage _checkFunctionUsage;
        ErrorLogger *_errorLogger;
};

#endif // CPPCHECK_H
