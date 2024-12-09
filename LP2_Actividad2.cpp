#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;

    // Creaci�n de la conexi�n usando ODBC
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Conexi�n a la base de datos que almacena la informaci�n de los empleados usando ODBC
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"IDS_SQLServer", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "Conectado a la base de datos exitosamente." << endl;

        SQLHSTMT hStmt;
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        // Impresi�n de los encabezados de la tabla de empleados
        wcout << L"+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+-----------+" << endl;
        wcout << L"| No. Empleado     | Nombre           | Apellido Paterno | Apellido Materno | Fecha Nacimiento | RFC              | Centro de Trabajo| Centro Numero    | Puesto           | Descripcion Puesto| Ciudad          | Directivo |" << endl;
        wcout << L"+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+-----------+" << endl;

        // Se omite la consulta de los datos y se muestran �nicamente los encabezados
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Finalizar la impresi�n de los bordes de la tabla de empleados, se omite
        // wcout << L"+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+-----------+" << endl;

        // Impresi�n de los encabezados de la tabla de directivos
        wcout << L"\n\n+------------------+---------------------+----------------------------+" << endl;
        wcout << L"| No. Empleado     | Centro Supervisado  | Prestacion de Combustible  |" << endl;
        wcout << L"+------------------+---------------------+----------------------------+" << endl;

        // Se omite la consulta de los datos y se muestran �nicamente los encabezados
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Finalizar la impresi�n de los bordes de la tabla de directivos, se omite
        // wcout << L"+------------------+---------------------+----------------------------+" << endl;
    }
    else {
        cout << "Fallo la conexion a la base de datos" << endl;
    }

    // Desconexi�n y liberaci�n de recursos
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}

