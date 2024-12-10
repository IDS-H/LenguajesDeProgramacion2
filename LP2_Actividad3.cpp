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

    // Asignar un gestor de entorno
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    // Asignar un gestor de conexión
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Conectarse a la base de datos
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"IDS_SQLServer", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "Conectado a la base de datos exitosamente." << endl;

        SQLHSTMT hStmt;
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        // Creación de los encabezados de la tabla
        wcout << L"+------+--------------------------------------------------+------------------+---------------+------------------------------+------------------------------------------------------------+-----------+" << endl;
        wcout << L"| No.  | Nombre Completo                                  | Fecha Nacimiento |    RFC        | Centro de Trabajo            | Descripcion Puesto                                         | Directivo |" << endl;
        wcout << L"+------+--------------------------------------------------+------------------+---------------+------------------------------+------------------------------------------------------------+-----------+" << endl;

        // Select a la base de datos
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Empleados", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            int num_empleado;
            SQLWCHAR name[50];
            SQLWCHAR last_name[50];
            SQLWCHAR slast_name[50];
            SQLWCHAR Birthday[50];
            SQLWCHAR RFC[50];
            SQLWCHAR CentroTrabajo[50];
            SQLWCHAR DescripcionPuesto[200]; // Se ha aumentado el tamaño para permitir descripciones más largas
            SQLWCHAR directivo[50];

            // Contador para limitar los resultados a 10 empleados y no saturar la tabla en caso de tener una lista extensa
            int count = 0;

            while (SQLFetch(hStmt) == SQL_SUCCESS && count < 10) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), NULL);
                SQLGetData(hStmt, 3, SQL_C_WCHAR, last_name, sizeof(last_name), NULL);
                SQLGetData(hStmt, 4, SQL_C_WCHAR, slast_name, sizeof(slast_name), NULL);
                SQLGetData(hStmt, 5, SQL_C_WCHAR, Birthday, sizeof(Birthday), NULL);
                SQLGetData(hStmt, 6, SQL_C_WCHAR, RFC, sizeof(RFC), NULL);
                SQLGetData(hStmt, 7, SQL_C_WCHAR, CentroTrabajo, sizeof(CentroTrabajo), NULL);
                SQLGetData(hStmt, 9, SQL_C_WCHAR, DescripcionPuesto, sizeof(DescripcionPuesto), NULL);
                SQLGetData(hStmt, 12, SQL_C_WCHAR, directivo, sizeof(directivo), NULL);

                // Concatenación de los apellidos para mostrar el nombre completo en una sola columna
                wstring last_names = wstring(last_name) + L" " + wstring(slast_name);
                wstring full_name = wstring(name) + L" " + last_names;
                wstring dir(directivo);
                wstring answer;

                // Convertir el valor de directivo a "Sí" o "No"
                if (dir == L"1") {
                    answer = L"Si";
                }
                else {
                    answer = L"No";
                }

                // Impresión de la tabla y ajuste de la longitud de las columnas para un correcto formato
                wcout << L"|" << setw(6) << left << num_empleado
                    << L"|" << setw(50) << left << full_name
                    << L"|" << setw(18) << left << Birthday
                    << L"|" << setw(15) << left << RFC
                    << L"|" << setw(30) << left << CentroTrabajo
                    << L"|" << setw(60) << left << DescripcionPuesto
                    << L"|" << setw(10) << left << answer << L" |" << endl;

                // Incrementar el contador
                count++;
            }

            wcout << L"+------+--------------------------------------------------+------------------+---------------+------------------------------+------------------------------------------------------------+-----------+" << endl;
        }

        // Liberar el manejador de conexión
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }
    else {
        cout << "Fallo la conexion a la base de datos" << endl;
    }

    // Desconectar y liberar gestores de entorno
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}
