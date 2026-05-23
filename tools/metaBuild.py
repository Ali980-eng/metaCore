import subprocess
from pathlib import Path
from typing import Callable
from typing import Any
from copy import deepcopy

class project:
    def __init__(self, name: str, description: str, version: float) -> None:
        self.__name = name
        self.__description = description
        self.__version = version

    @property
    def name(self) -> str:
        return self.__name

    @property
    def description(self) -> str:
        return self.__description

    @property
    def version(self) -> float:
        return self.__version

    def __str__(self) -> str:
        return (
            f"Project: {self.__name}\n"
            f"Description: {self.__description}\n"
            f"Version: {self.__version}\n"
        )

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, project):
            return False
        return (
            self.__name == other.__name
            and self.__description == other.__description
            and self.__version == other.__version
        )

class builder:
    def __init__(self) -> None:
        self.__details: project | None = None
        self.__procedures: dict[str, Callable[[], None]] = {}
        self.__compiler: tuple[str, Path] = ("", Path())
        self.__includes: list[Path] = []
        self.__sources: list[Path] = []
        self.__flags: list[str] = []

    @property
    def details(self) -> project | None:
        return self.__details

    @property
    def compiler(self) -> tuple[str, Path]:
        return self.__compiler

    @property
    def includes(self) -> list[Path]:
        return deepcopy(self.__includes)

    @property
    def sources(self) -> list[Path]:
        return deepcopy(self.__sources)

    @property
    def flags(self) -> list[str]:
        return deepcopy(self.__flags)

    def setProject(self, name: str, description: str, version: float) -> None:
        if not name.strip():
            raise ValueError("Project name cannot be empty.")
        if not description.strip():
            raise ValueError("Project description cannot be empty.")
        if version <= 0.0:
            raise ValueError("Version must be greater than zero.")
        self.__details = project(name, description, version)

    def set_compiler(self, name: str) -> None:
        if not name.strip():
            raise ValueError("Compiler name cannot be empty.")
        self.__compiler = (name, "")

    def setCompiler(self, name: str, path: Path) -> None:
        if not name.strip():
            raise ValueError("Compiler name cannot be empty.")
        if not path.exists():
            raise FileNotFoundError(f"Compiler path does not exist: {path}")
        self.__compiler = (name, path)

    def addIncludePath(self, path: Path) -> None:
        if not path.is_dir():
            raise NotADirectoryError(f"Include path is not a valid directory: {path}")
        if path in self.__includes:
            raise ValueError(f"Include path already exists: {path}")
        self.__includes.append(path)

    def addSourcePath(self, path: Path) -> None:
        if not path.is_dir():
            raise FileNotFoundError(f"Source file does not exist: {path}")
        if path in self.__sources:
            raise ValueError(f"Source path already exists: {path}")
        self.__sources.append(path)

    def addFlag(self, flag: str) -> None:
        if not flag.strip():
            raise ValueError("Flag cannot be empty.")
        if flag in self.__flags:
            raise ValueError(f"Flag already exists: {flag}")
        self.__flags.append(flag)

    def add_procedure(
        self,
        name: str,
        procedure: Callable[..., None],
        *args: Any,
        **kwargs: Any
    ) -> None:
        if name in self.__procedures:
            raise ValueError(f"Procedure '{name}' already exists.")
        self.__procedures[name] = lambda: procedure(*args, **kwargs)

    def addProcedure(self, name: str, procedure: Callable[[], None]) -> None:
        if not name.strip():
            raise ValueError("Procedure name cannot be empty.")
        if name in self.__procedures:
            raise ValueError(f"Procedure '{name}' already exists.")
        self.__procedures[name] = procedure

    def getProcedure(self, name: str) -> Callable[[], None]:
        if name not in self.__procedures:
            raise KeyError(f"Procedure '{name}' not found.")
        return self.__procedures[name]

    def getCompilerName(self) -> str:
        return self.__compiler[0]
    
    def getCompilerPath(self) -> Path:
        return self.__compiler[1]
    
    def getCompiler(self, isName: bool):
        if isName: return self.getCompilerName
        else: self.getCompilerPath
    
    def getCompiler(self) -> tuple[str, Path]:
        return self.__compiler
    
    def getProjectName(self) -> str:
        return self.__details.__name
    
    def getProjectDescription(self) -> str:
        return self.__details.__description
    
    def getProject(self, isName: bool) -> str:
        if isName: return self.__details.__name
        else: return self.__details.__description
    
    def getVersion(self) -> float:
        return self.__details.__version
    
    # $function getFalg will return a flag from the flags in the object.
    # $parameter position is the index of the flag in flags.
    # $return the flag in string format.
    def getFalg(self, position: int) -> str:
        return self.__flags[position]

    # $function run will run a procedure from the procedures of the object.
    # $parameter name is string to search in procedures.
    # $return no value from this function.
    # $note if the name doesn't exist in procedures. \
    #  the function will raise KeyError.
    def run(self, name: str) -> None:
        if name not in self.__procedures:
            raise KeyError(f"Procedure '{name}' not found.")
        self.__procedures[name]()

    # $function runAll will run all procedures in the object.
    def runAll(self) -> None:
        for procedure in self.__procedures.values():
            procedure()

def execute(command: list[str]) -> None:
    try:
        result = subprocess.run(
            command,
            capture_output=True,
            text=True,
            check=True
        )
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        raise RuntimeError(f"Command failed: {e.stderr}")