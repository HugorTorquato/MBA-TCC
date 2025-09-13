// ============================================================================
// Exemplo de classes fictícias para análise de herança em C++
// Contexto: sistema de zoológico e administração de recursos
// ============================================================================

// Classe base genérica para todos os animais
class Animal {
public:
    virtual void emitirSom() = 0; // método abstrato
};

// Classes especializadas por tipo
class Mamifero : public Animal {
public:
    virtual void amamentar() = 0;
};

class Ave : public Animal {
public:
    virtual void voar() = 0;
};

class Reptil : public Animal {
public:
    virtual void rastejar() = 0;
};

// ============================================================================
// Exemplos de animais concretos
// ============================================================================
class Leao : public Mamifero {};
class Tigre : public Mamifero {};
class Elefante : public Mamifero {};

class Papagaio : public Ave {};
class Aguia : public Ave {};
class Pato : public Ave {};

class Cobra : public Reptil {};
class Jacare : public Reptil {};

// ============================================================================
// Exemplo de múltipla herança
// ============================================================================
class AnimalAquatico {
public:
    virtual void nadar() = 0;
};

class PatoAquatico : public Ave, public AnimalAquatico {};
class JacareAquatico : public Reptil, public AnimalAquatico {};

// ============================================================================
// Hierarquia administrativa (funcionários e recursos do zoológico)
// ============================================================================
class Recurso {
public:
    virtual void alocar() = 0;
};

class Funcionario : public Recurso {};
class Veterinario : public Funcionario {};
class Cuidador : public Funcionario {};
class Administrador : public Funcionario {};

class Jaula : public Recurso {};
class Aquario : public Recurso {};
class Viveiro : public Recurso {};

// ============================================================================
// Classes que representam sistemas de gestão
// ============================================================================
class SistemaGerenciamento {
public:
    // Apenas borda da classe
};

class SistemaFinanceiro : public SistemaGerenciamento {};
class SistemaVeterinario : public SistemaGerenciamento {};
class SistemaVisitantes : public SistemaGerenciamento {};

// ============================================================================
// Combinação de domínios distintos
// ============================================================================
class Zoologico {
public:
    // Apenas borda da classe
};

class ZoologicoDigital : public Zoologico, public Recurso {};