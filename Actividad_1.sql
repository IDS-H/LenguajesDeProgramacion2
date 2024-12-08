-- Creaci�n de la tabla de Empleados
CREATE TABLE Empleados
(
    Numero_Empleado INT IDENTITY(1,1) PRIMARY KEY,
    Nombre VARCHAR(50) NOT NULL,
    Apellido_Paterno VARCHAR(50) NOT NULL,
    Apellido_Materno VARCHAR(50) NOT NULL,
    Fecha_Nacimiento DATE NOT NULL,
    RFC AS (UPPER(SUBSTRING(Nombre,1,2) + SUBSTRING(Apellido_Paterno,1,2) +
                 SUBSTRING(Apellido_Materno,1,1) +
                 CONVERT(VARCHAR, YEAR(Fecha_Nacimiento)) + 
                 RIGHT('00' + CONVERT(VARCHAR, MONTH(Fecha_Nacimiento)), 2) + 
                 RIGHT('00' + CONVERT(VARCHAR, DAY(Fecha_Nacimiento)), 2))),
    Centro_Trabajo VARCHAR(50) NOT NULL,
    Centro_Numero INT NOT NULL,
    Puesto VARCHAR(50) NOT NULL,
    Descripcion_Puesto VARCHAR(200) NOT NULL,
    Ciudad VARCHAR(50) NOT NULL,
    Directivo BIT NOT NULL
);

-- Registro de informaci�n en la tabla de Empleados
INSERT INTO Empleados
(Nombre, Apellido_Paterno, Apellido_Materno, Fecha_Nacimiento, Centro_Trabajo, Centro_Numero, Puesto, Descripcion_Puesto, Ciudad, Directivo)
VALUES
('Berenice', 'Rivera', 'Astorga', '1996-06-15', 'Dise�o', 230836, 'Arquitecto', 'Responsable de dibujar planos arquitect�nicos y apoyar al L�der de Proyecto', 'Culiac�n', 0),
('Fernanda', 'Rom�n', 'Zavala', '1989-05-28', 'Dise�o', 230836, 'Gerente', 'Responsable del equipo multidisciplinario', 'Culiac�n', 1),
('Fernando', 'Cervantes', 'Arellano', '1990-09-27', 'Marketing', 230837, 'L�der de Marketing', 'Responsable de la planificaci�n de campa�as publicitarias y medios', 'Culiac�n', 0),
('Hern�n', 'Vel', 'Za', '1989-05-01', 'Dise�o', 230850, 'Coordinador de Proyectos', 'Gesti�n y administraci�n del equipo de gerentes', 'Culiac�n', 1),
('Carol', 'Santana', 'Garc�a', '1998-12-23', 'Proyectos', 230860, 'L�der de Proyecto', 'Desarrollo de proyectos arquitect�nicos en conjunto con las ingenier�as', 'Culiac�n', 0);

-- Verificaci�n y muestra de la tabla
SELECT * FROM Empleados

-- Creaci�n de la tabla de Directivos
CREATE TABLE Directivos
(
    Numero_Empleado INT PRIMARY KEY, 
    Centro_Supervisado INT NOT NULL DEFAULT 0, 
    Prestacion_Combustible BIT NOT NULL 
);

-- Registro de los empleados Directivos en la tabla
INSERT INTO Directivos(Numero_Empleado, Centro_Supervisado, Prestacion_Combustible)
SELECT Numero_Empleado, 0, 1 
FROM Empleados
WHERE Directivo = 1;

-- Verificaci�n y muestra de la tabla
SELECT * FROM Directivos;


