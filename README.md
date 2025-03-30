# NTU Notes Repository

## About
Basically for everyone. From course map if you want to see syllabus/ people who want to see notes for planning future modules, as of now it is mainly robotics but I think if an issue is raised/Discussion is made, I think it can be done. Right now focusing on Robotics mods but I think I will include the other BDE mods in case anyone wants the notes from there and those school like LG5001 for example.
This repository was made to ensure the safety and anonyminity of the uploads. People who use this repository are advised to update it with their notes as I can only scrape so far into the past and I do not know how much the syllabus has changed since then. I also recommend forking the repository in the event someone goes and say "I found it online" etc, so in the event one repo goes down, there are others still out there. Though this is a decentralized way of note sharing via github, I will make one static folder on MEGA or something when I feel confident on the first iteration of this repository. 

#### (For now you can just put download via zip from the top right)

### Note: 
- As Github can get anonymous, if you want to leave your credit like Tutorial 1 by XXX or provide some help in the README.md (I will get around to writing the README for each module to mention the books etc), go ahead. Or text me via the contacts below and I will get back to you when I turn my phone on.
- Do make issues with regards to missing stuff (especially the books asked by that they will use and I will most prob find like E.g. An Introduction to Planar Dynamics by Professor Yap Fook Fah), I tried my best to find notes and will be regularly updating this(if i can) and I recommend git pulling from time to time. There will be mistakes (and duplicates), but we(I and my brother) will do our best to fix it.
- If you want to help out, you can reach out to me directly.(You know my actual Tele handle, otherwise scroll to the bottom -W)
- I am aware of the coursehero paywall shit, probably gonna buy some third-party key for a day to download all the documents but if anyone else has a recommendation I do appreciate it.
- For older modules that were taken, we are working to sanitize people's names from some of the work so it doesn't lead back to anyone. Those that I grabbed online, well I will keep it there cuz it was already publicly available.

### I'm rewriting this README from a ChatGPT template so cut me some slack. If you are uncertain how git works, please scroll to the bottom tutorial.

## Repository Structure (Will probably rework this soon)

### `<College> -> <School> -> <Module>`

```
NTU-Notes/
├── Engineering/
│   └── Mechanical/
├── Humanities/
└── Modern-Languages/
```

## Repository Content
We accept everything to be honest, just so long as it doesnt exist so we don't get duplicates. Or fork it yourself.

## Branch Protection and Content Guidelines
To maintain quality and organization, we've implemented the following protections:

### Branch Rules
- All changes must be submitted through pull requests (as is usual with git); direct pushes to the main branch are not allowed
- Make a new branch outside of main with 
```
git switch -c <branch name>
```
Otherwise just fork it and add it from there, though it will probably be alot easier if everyone kind of just puts it together first then fork it.

### Content Guidelines
- Place materials in appropriate course folders
- Follow naming convention if possible
- Please avoid overlapping documents

## Tutorial for Getting Started with Git (For First-Time Contributors)

### One-Time Setup
1. Install Git on your computer:
   - Windows: Download and install Git from [git-scm.com](https://git-scm.com/)
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
   cd Engineering/Mechanical/
   ```

4. Stage your changes:
   ```bash
   git add .                 # Add all files
   # OR
   git add specific-file.pdf # Add specific file
   ```

5. Commit your changes; must include a message:
   ```bash
   git commit -m "Add notes for Ma2011 Week 3"
   ```

6. Push your changes:
- First time:
   ```bash
   git push origin add-my-notes
   ```
- Subsequent times:
   ```bash
   git push
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
- `git checkout branch-name` OR `git switch branch -name`: Switch to a different branch

## Additional Resources
- [Git Documentation](https://git-scm.com/doc)
- [GitHub Guides](https://guides.github.com)
- [GitHub Issues](../../issues)

## Content Concerns
If you have concerns about any content in this repository:
1. Create an [Issue](../../issues) in the repository detailing your concern
2. Reach out directly via the contact methods listed below
3. For urgent matters, you can also contact us through Telegram/WhatsApp for faster response

We believe in open access to educational materials while respecting intellectual property rights. We're happy to:
- Discuss any concerns about hosted content
- Work with content owners to find appropriate solutions
- Remove content if requested through proper channels
- Add appropriate attribution where needed

## Contact and Support

### Getting in Touch
Have questions? Want to contribute but not sure how? Don't hesitate to reach out:
- Email: goldenhaleingermany@gmail.com
- WhatsApp/Telegram: +4917685209054

### Attribution and Recognition
If you wish to credit yourself you can probably do it like 
```
Tutorial1-Solutions[Yandex(Tyler1)].pdf
```

### Common Concerns
- "What if I mess up the repository?" Don't worry! Git keeps track of all changes, and we can always revert to a previous version. No change is permanent.

## Credits
Big thanks to my brother Warren for helping.
