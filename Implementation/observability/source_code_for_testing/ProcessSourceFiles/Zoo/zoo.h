// ============================================================================
// Exemplo de classes fictícias para análise de herança em C++
// Contexto: sistema de zoológico e administração de recursos
// ============================================================================

// Classe base genérica para todos os animais
class Animal {
public:
    virtual void emitirSom() = 0; // método abstrato
};

// Classe de mamíferos herda de Animal
class Mamifero : public Animal {
public:
    virtual void amamentar() = 0;
};

// Classe de aves herda de Animal
class Ave : public Animal {
public:
    virtual void voar() = 0;
};

// Classe de répteis herda de Animal
class Reptil : public Animal {
public:
    virtual void rastejar() = 0;
};

// Classes específicas
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
// Exemplo de herança virtual (evitando duplicação de Animal)
// ============================================================================
class AnimalDomestico : virtual public Animal {};
class AnimalDeEstimacao : virtual public Animal {};

class Cachorro : public Mamifero, public AnimalDomestico, public AnimalDeEstimacao {};
class Gato : public Mamifero, public AnimalDomestico, public AnimalDeEstimacao {};

// ============================================================================
// Exemplo de hierarquia administrativa (não animais, mas gestão)
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
// Classes que combinam domínios distintos
// ============================================================================
class Zoologico {
public:
    // Apenas borda da classe
};

class ZoologicoDigital : public Zoologico, public Recurso {};

class SistemaGerenciamento {
public:
    // Apenas borda da classe
};

class SistemaFinanceiro : public SistemaGerenciamento {};
class SistemaVeterinario : public SistemaGerenciamento {};
class SistemaVisitantes : public SistemaGerenciamento {};
