# NTU Notes Repository

## About This Project
This repository serves as a collaborative learning resource for NTU students. Our goal is to create a comprehensive collection of student-created study materials that can help fellow students better understand their coursework.

## Repository Structure
```
NTU-Notes/
├── Engineering/
│   ├── Mechanical/
│   │   ├── Common/
│   │   │   └── [Course Code]-[Course Name]/
│   │   ├── Robotics/
│   │   │   └── [Course Code]-[Course Name]/
│   │   └── Aerospace/
│   │       └── [Course Code]-[Course Name]/
├── Humanities/
└── Modern-Languages/
```

## Getting Started with Git (For First-Time Contributors)

### One-Time Setup
1. Install Git on your computer:
   - Windows: Download and install Git from https://git-scm.com/
   - Linux: `sudo apt-get install git` (Ubuntu/Debian)
   - Mac: Install via Homebrew: `brew install git`

2. Configure Git with your information:
   ```bash
   git config --global user.name "Your Name"
   git config --global user.email "your.email@example.com"
   ```

3. Set up SSH key (for secure connection to GitHub):
   ```bash
   ssh-keygen -t ed25519 -C "your.email@example.com"
   ```
   - Add the generated key to your GitHub account (Settings → SSH Keys)

### Contributing to the Repository

#### First Time Setup
1. Fork the repository (click 'Fork' button on GitHub)
2. Clone your fork to your computer:
   ```bash
   git clone git@github.com:YOUR-USERNAME/NTU-Notes.git
   cd NTU-Notes
   ```

#### Making Changes (Every Time You Want to Contribute)
1. Get the latest updates:
   ```bash
   git pull origin main
   ```

2. Create a new branch for your changes:
   ```bash
   git checkout -b add-my-notes
   ```

3. Add your files to the appropriate folder
   ```bash
   # Example: Adding notes for a robotics course
   cd Engineering/Mechanical/Robotics/ME2121-Mechanics
   ```

4. Stage your changes:
   ```bash
   git add .                 # Add all files
   # OR
   git add specific-file.pdf # Add specific file
   ```

5. Commit your changes:
   ```bash
   git commit -m "Add notes for ME2121 Week 3"
   ```

6. Push your changes:
   ```bash
   git push origin add-my-notes
   ```

7. Create a Pull Request:
   - Go to GitHub
   - Click 'Pull Request'
   - Select your branch
   - Click 'Create Pull Request'

### Common Git Commands Explained
- `git status`: Check what files have been changed
- `git diff`: See exactly what changed in files
- `git log`: See history of changes
- `git branch`: List all branches
- `git checkout branch-name`: Switch to a different branch

## Contribution Guidelines

### Acceptable Content
- Student-created study notes
- Practice problems and solutions
- Study guides and summaries
- Learning resources and references
- Code examples and explanations

### File Naming Convention
Please follow this format for all submissions:
```
[Course Code]-[Course Name]/
└── [Week/Topic]-[Description].[extension]
```
Example:
```
ME2121-Engineering-Mechanics/
├── Week1-Introduction-to-Forces.pdf
└── Tutorial2-Solutions.pdf
```

### Academic Integrity Notice
This repository is intended for educational purposes and collaborative learning. Contributors and users should:
1. Only share their own original work
2. Properly cite any referenced materials
3. Use these materials as study aids, not substitutes for course participation
4. Follow NTU's academic integrity guidelines

## Contact and Support

### Getting in Touch
Have questions? Want to contribute but not sure how? Don't hesitate to reach out:
- Email: <your-email>
- Telegram: <your-handle>
- WhatsApp: <your-number>

### Attribution and Recognition
We believe in giving credit where credit is due. All contributions will be recognized in the following format:
- Student-created content: "Contributed by [Your Name/Handle]"
- Retrieved content: "[Source (Author if available)]"
- Anonymous contributions are welcome - just let us know if you prefer to remain unnamed

### Common Concerns
- "What if I mess up the repository?" Don't worry! Git keeps track of all changes, and we can always revert to a previous version. No change is permanent.
- "I'm not sure if my contribution fits." Reach out to us! We're happy to discuss and guide you through the process.
- "I don't understand Git." That's completely normal! We all started there. Feel free to contact us for step-by-step guidance.

## Need Help?
- If you're stuck with Git: Check out [Git's official documentation](https://git-scm.com/doc)
- For repository-specific questions: Open an issue in this repository
- For general GitHub help: Visit [GitHub Docs](https://docs.github.com)

Remember: Everyone starts somewhere! Don't be afraid to ask questions or make mistakes - that's part of learning!