/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Gui;

import Exceptions.BadAlloc;
import Exceptions.TFFLFileNotExistException;
import com.jp.tffl.FileOperations.FileOperations;
import com.jp.tffl.Person.Player;
import com.jp.tffl.Person.TFFLManager;
import com.jp.tffl.Person.TeamManager;
import com.jp.tffl.Table.ScheduleTable;
import com.jp.tffl.Table.ScoreTable;
import com.jp.tffl.Table.StandingTable;
import com.jp.tffl.Team.Team;
import com.jp.tffl.TeamOperations.Schedule2Team;
import com.jp.tffl.TeamOperations.Score2Team;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTable;
import javax.swing.SwingConstants;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import jdk.nashorn.internal.runtime.Logging;
import sun.swing.table.DefaultTableCellHeaderRenderer;


/**
 *
 * @author Jason
 */
public class TFFLGui extends javax.swing.JFrame
{
    TFFLManager president;
    TFFLManager vicePresident;
    int weekNumber = 0;
    private String mainFolder;
    private JFileChooser chooser = new JFileChooser();
    
    
    /**
     * Creates new form TFFLGui
     * @throws java.io.IOException
     * @throws java.lang.CloneNotSupportedException
     * @throws java.lang.ClassNotFoundException
     * @throws java.io.FileNotFoundException
     * @throws Exceptions.TFFLFileNotExistException
     * @throws Exceptions.BadAlloc
     * @throws java.lang.InstantiationException
     * @throws java.lang.IllegalAccessException
     * @throws javax.swing.UnsupportedLookAndFeelException
     */
    public TFFLGui() throws IOException, CloneNotSupportedException, ClassNotFoundException, FileNotFoundException, TFFLFileNotExistException, BadAlloc, InstantiationException, IllegalAccessException, UnsupportedLookAndFeelException 
    {
    /*   
        FileOperations.deleteFolder(Paths.get("Teams"));
        FileOperations.deleteFolder(Paths.get("Players"));
        FileOperations.deleteFolder(Paths.get("TFFL Managers"));
        FileOperations.deleteFolder(Paths.get("Team managers"));
        FileOperations.deleteFolder(Paths.get("Schedules"));
        FileOperations.deleteFolder(Paths.get("Standing Tables"));
        FileOperations.deleteFolder(Paths.get("Scores"));*/
        

        chooser = new JFileChooser(); 
        chooser.setCurrentDirectory(new java.io.File("."));
        chooser.setDialogTitle("Select your league folder");
        chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        chooser.setAcceptAllFileFilterUsed(false);

        do{
            if (chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION)
                mainFolder = chooser.getSelectedFile().toString() + "/";
            else
            {
                JOptionPane.showMessageDialog(this,"any file was did not selected, system will not open");
                System.exit(0);
            }

            if(!new File(mainFolder + "Teams").isDirectory() && !new File(mainFolder + "Teams.csv").exists())
                JOptionPane.showMessageDialog(this, "Missing files, returning");
        }while(!new File(mainFolder + "Teams").isDirectory() && !new File(mainFolder + "Teams.csv").exists());
        
        initComponents();
        
        if(new File(mainFolder + "weekNumber.dat").exists())
            this.weekNumber = (Integer) FileOperations.readBinary(mainFolder + "weekNumber.dat");
        
        
        if(!Files.isDirectory(Paths.get(mainFolder + "Teams")))
        {           
            this.readTeams(mainFolder + "Teams");
            this.readTFFLManagers();
            this.readTeamManagers();
            this.readPlayers();
            this.verifyDatas();
            this.matchDatas();
            this.autoSchedule();
            this.createStandings();
        }
        this.pictureBox.setIcon(new javax.swing.ImageIcon(mainFolder + "logo.jpg"));


        this.setupTables();
        this.fillStandingTable(this.weekNumber);
        this.setTableRender(scoreTable.getColumnCount(),scoreTable);
        this.clearTable(scoreTable);

    }
    

    private void createStandings() throws IOException, FileNotFoundException, ClassNotFoundException
    {
        File folder = new File(mainFolder + "Teams");
        File [] files = folder.listFiles();
        ArrayList<Team> teams = new ArrayList<>();
        StandingTable standTab = new StandingTable(this.weekNumber);
        for (int i = 0; i < files.length; i++) 
            teams.add((Team) FileOperations.readBinary(mainFolder + "Teams/" + files[i].getName()));
        
        
        Collections.sort(teams);
        
        for (int i = 0; i < teams.size(); i++) 
        {
            standTab.add(teams.get(i).getName(), teams.get(i).getScore(), teams.get(i).getWin(), teams.get(i).getLose(),
                         teams.get(i).getDraw(), teams.get(i).getGoalsFor(), teams.get(i).getGoalsAgainst());
        }
    
         folder = new File(mainFolder + "Standing Tables");
         if(!folder.isDirectory())
             folder.mkdir();
         FileOperations.writeBinary(standTab, mainFolder + "Standing Tables/table" + this.weekNumber + ".dat");
         
         fillStandingTable(this.weekNumber);
    
    }
    
    
    private void fillStandingTable(int week) throws IOException, FileNotFoundException, ClassNotFoundException
    {
        
        StandingTable table = (StandingTable) FileOperations.readBinary(mainFolder + "Standing Tables/table" + week + ".dat");
        
        
        for (int i = 0; i < table.size(); i++) 
        {
            this.standingTable.setValueAt(i+1, i, 0);
            this.standingTable.setValueAt(table.getTeams()[i], i, 1);
            this.standingTable.setValueAt(table.getWeekNumber(), i, 2);
            this.standingTable.setValueAt(table.getScores()[i], i, 3);
            this.standingTable.setValueAt(table.getWins()[i], i, 4);
            this.standingTable.setValueAt(table.getLoses()[i], i, 5);
            this.standingTable.setValueAt(table.getDraws()[i], i, 6);
            this.standingTable.setValueAt(table.getGoalsFor()[i], i, 7);
            this.standingTable.setValueAt(table.getGoalsAgainsts()[i], i, 8);
            this.standingTable.setValueAt(table.getGoalsFor()[i] - table.getGoalsAgainsts()[i], i, 9);            
        }

            
        this.setTableRender(this.standingTable.getColumnCount(), this.standingTable);

        
    }

    private void readTFFLManagers() throws IOException, CloneNotSupportedException, ClassNotFoundException
    {
        TFFLManager tfflManager;
        String line;
        String className = mainFolder + "TFFL Managers";
        BufferedReader fileScan = new BufferedReader(new FileReader(className + ".csv"));
        while((line = fileScan.readLine()) != null)
        {           
            tfflManager = new TFFLManager(line);
            new File(className).mkdir();
            FileOperations.writeBinary(tfflManager, className + "/"+tfflManager.getID()+".dat");
            tfflManager = null;
        }
  
        
    }
    
    
    private void readTeamManagers() throws IOException, CloneNotSupportedException, ClassNotFoundException
    {
        String line;
        TeamManager teamManager;
        String className = mainFolder + "Team Managers";
        BufferedReader fileScan = new BufferedReader(new FileReader(className + ".csv"));
        while((line = fileScan.readLine()) != null)
        {           
            teamManager = new TeamManager(line);
            new File(className).mkdir();
            FileOperations.writeBinary(teamManager, className + "/"+teamManager.getID()+".dat");
            teamManager = null;
        }
  
    }
    
 
    private void readPlayers() throws IOException, CloneNotSupportedException, ClassNotFoundException
    {
        String line;
        Player player;
        String className = mainFolder + "Players";
        BufferedReader fileScan = new BufferedReader(new FileReader(className + ".csv"));
        while((line = fileScan.readLine()) != null)
        {           
            player = new Player(line);
            new File(className).mkdir();
            FileOperations.writeBinary(player, className + "/"+player.getID()+".dat");
            player = null;
        }
  
    }
   
     
    
    private void readTeams(String className) throws IOException, CloneNotSupportedException, ClassNotFoundException, BadAlloc
    {
        String line;
        Team team;
        BufferedReader fileScan = new BufferedReader(new FileReader(className + ".csv"));
        while((line = fileScan.readLine()) != null)
        {           
            team = new Team(line);
            new File(className).mkdir();
            FileOperations.writeBinary(team, className + "/"+team.getName()+".dat");
            team = null;
        }
  
    }
    
    
    
    private void verifyDatas() throws IOException, FileNotFoundException, ClassNotFoundException, TFFLFileNotExistException
    {
        File folder = new File(mainFolder + "Players");
        File [] files = folder.listFiles();

        for (int i = 0; i < files.length; i++)
        {
            Player tempPlayer = (Player) FileOperations.readBinary(mainFolder + "Players/" + files[i].getName());
            File tempFile = new File(mainFolder + "Teams/" + tempPlayer.getTeam() + ".dat");
             if(!tempFile.isFile())
             {
                 throw new TFFLFileNotExistException();

             }
        }
        folder = null ; files = null;
    
        folder = new File(mainFolder + "Team Managers");
        files = folder.listFiles();
        
        for (int i = 0; i < files.length; i++)
        {
            TeamManager temp = (TeamManager) FileOperations.readBinary(mainFolder + "Team Managers/" + files[i].getName());
            File tempFile = new File(mainFolder + "Teams/" + temp.getTeam() + ".dat");
            if(!tempFile.isFile())
                throw new TFFLFileNotExistException();

        }
        
        System.out.println("Files were verified..");
    }
    
    
    private void matchDatas() throws IOException, FileNotFoundException, ClassNotFoundException
    {
        File folder = new File(mainFolder + "Players");
        File [] files = folder.listFiles();

        for (int i = 0; i < files.length; i++)
        {
            Player tempPlayer = (Player) FileOperations.readBinary(mainFolder + "Players/" + files[i].getName());      
            Team tempTeam = (Team) FileOperations.readBinary(mainFolder + "Teams/" + tempPlayer.getTeam() + ".dat");
            if(tempTeam.getName().equals(tempPlayer.getTeam()))
            {
                tempTeam.addPlayer(tempPlayer.getID());
                FileOperations.writeBinary(tempTeam, mainFolder + "Teams/" + tempPlayer.getTeam() + ".dat");
            }
        }
        
      Player tempPlayer = (Player) FileOperations.readBinary(mainFolder + "Players/" + files[2].getName());      
      Team tempTeam = (Team) FileOperations.readBinary(mainFolder + "Teams/" + tempPlayer.getTeam() + ".dat");
    }
   
    
    private void setupTables() throws IOException, FileNotFoundException, ClassNotFoundException
    {   
        File folder = new File(mainFolder + "Teams");
        File [] files = folder.listFiles();
        String [] scoreList = new String[files.length];
    
        for (int i = 0; i < files.length; i++) 
        {
            Team tempTeam = (Team) FileOperations.readBinary(mainFolder + "Teams/" + files[i].getName());
            scoreList[i] = tempTeam.getName() + "   " + this.weekNumber + "   " + tempTeam.getScore();
        }
    
    
    }
    
    private void autoSchedule() throws IOException, CloneNotSupportedException
    {
        File folder = new File(mainFolder + "Schedules");
        if(!folder.isDirectory())
            folder.mkdir();

        folder = new File(mainFolder + "Teams");
        File [] files = folder.listFiles();
        ArrayList<String> teams = new ArrayList<>();
        ArrayList<Schedule2Team> sch = new ArrayList<>();
        
        for (int i = 0; i < files.length; i++) 
        {
            int pos = files[i].getName().lastIndexOf(".");
            teams.add(files[i].getName().substring(0, pos));
        }
        int week = 1;
        int week2 = 34;
        String tempTeam;
        ScheduleTable temp = new ScheduleTable();
        ScheduleTable temp2 = new ScheduleTable();

        for (int j = 0; j < teams.size()-1; j++) 
        {
            for (int i = 0; i < teams.size()/2; i++)
            {
                temp.addSchedule(new Schedule2Team(teams.get(i), teams.get(teams.size()-1-i), week, "20.00"));
                temp2.addSchedule(new Schedule2Team(teams.get(teams.size()-1-i), teams.get(i), week, "18.00"));

            }
            temp.setWeekNumber(week);
            FileOperations.writeBinary(temp, mainFolder + "Schedules/scheduleWeek" + week + ".dat");     
            FileOperations.writeBinary(temp2, mainFolder + "Schedules/scheduleWeek" + week2 + ".dat");     

            temp.removeAll();
            temp2.removeAll();
            week++;
            week2--;
            
            tempTeam = teams.get(1);
            for (int i = 1; i < teams.size()-1; i++) 
                teams.set(i, teams.get(i+1));
            teams.set(teams.size()-1, tempTeam);
        }
        
    }
    
    private int random(int min, int max)
    {
        Random rand = new Random();
        
        return rand.nextInt(max-min) + min;
    
    }
    
    
    private void win(String teamName, int goalsFor, int goalsAgainst) throws FileNotFoundException, ClassNotFoundException, IOException
    {
        Team team = (Team) FileOperations.readBinary(mainFolder + "Teams/" + teamName + ".dat");
        team.win(goalsFor, goalsAgainst);
              
        FileOperations.writeBinary(team, mainFolder + "Teams/" + teamName + ".dat");

    }
    
    private void draw(String teamName, int goalsFor, int goalsAgainst) throws IOException, FileNotFoundException, ClassNotFoundException
    {
        Team team = (Team) FileOperations.readBinary(mainFolder + "Teams/" + teamName + ".dat");
        team.draw(goalsFor, goalsAgainst);
        FileOperations.writeBinary(team, mainFolder + "Teams/" + teamName + ".dat");
       
    }
    
    private void lose(String teamName, int goalsFor, int goalsAgainst) throws IOException, FileNotFoundException, ClassNotFoundException
    {
        Team team = (Team) FileOperations.readBinary(mainFolder + "Teams/" + teamName + ".dat");
        team.lose(goalsFor, goalsAgainst);
        FileOperations.writeBinary(team, mainFolder + "Teams/" + teamName + ".dat");
       
    }
    
    private void goal(String teamName, int number) throws IOException, FileNotFoundException, ClassNotFoundException
    {
        Team team = (Team) FileOperations.readBinary(mainFolder + "Teams/" + teamName + ".dat");
        String [] players = team.getPlayers();
        Player player = (Player) FileOperations.readBinary(mainFolder + "Players/" + players[number] + ".dat");
        
        player.goal();
        
        FileOperations.writeBinary(player, mainFolder + "Players/" + players[number] + ".dat");
        
    }
    
    private void createScoreTable(int week) throws IOException, FileNotFoundException, ClassNotFoundException, CloneNotSupportedException
    {
        if(this.weekNumber == 0)
            return;
        
        ScheduleTable table;
        ScoreTable scoreTab = new ScoreTable();
        Score2Team s2t;
        
        table = (ScheduleTable) FileOperations.readBinary(mainFolder + "Schedules/scheduleWeek" + week + ".dat");

        for (int i = 0; i < table.size(); i++) 
        {
            int score1 = this.random(0, 7);
            int score2 = this.random(0, 7);
            for (int j = 0; j < score1; j++)
            {
                this.goal(table.get(i).getTeam1(), this.random(0, 10));
            }
            
            for (int k = 0; k < score2; k++)
            {
                this.goal(table.get(i).getTeam2(), this.random(0, 10));
            }
            s2t = new Score2Team(table.get(i).getTeam1(), score1, table.get(i).getTeam2(), score2, week,table.get(i).getTime() );
            scoreTab.addScore(s2t);

            try
            {
                if(score1 > score2)
                {
                    this.win(s2t.getTeam1(), score1, score2);
                    this.lose(s2t.getTeam2(), score2, score1);
                }
                else if(score1 < score2)
                {
                    this.win(s2t.getTeam2(), score2, score1);
                    this.lose(s2t.getTeam1(), score1, score2);
                }
                else
                {
                    this.draw(s2t.getTeam1(), score1, score2);
                    this.draw(s2t.getTeam2(), score1, score2);
                }
            }  
            catch (IOException | ClassNotFoundException | CloneNotSupportedException ex)
            {
                Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        File folder = new File(mainFolder + "Scores");
        if(!folder.isDirectory())
            folder.mkdir();
        FileOperations.writeBinary(scoreTab, mainFolder + "Scores/score" + week + ".dat");
        scoreTab.removeAll();
        
        createStandings();
    }
    
    private void topScorer() throws IOException, FileNotFoundException, ClassNotFoundException
    {
        File folder = new File(mainFolder + "Players");
        File [] files = folder.listFiles();
        ArrayList<Player> players = new ArrayList<>();
        
        for (int i = 0; i < files.length; i++)
            players.add((Player)FileOperations.readBinary(mainFolder + "Players/" + files[i].getName()));
    
        Collections.sort(players);
        
        for (int i = 0; i < 20; i++) 
        {
            this.topScorersTable.setValueAt(players.get(i).getName(), i, 0);
            this.topScorersTable.setValueAt(players.get(i).getTeam(), i, 1);
            this.topScorersTable.setValueAt(players.get(i).getGoal(), i, 2);
        }
        
    }
    
    
    
    
    
    private void playOneWeek() throws IOException, FileNotFoundException, ClassNotFoundException, CloneNotSupportedException
    {
        this.weekNumber++;  
        this.createScoreTable(this.weekNumber);
        FileOperations.writeBinary(new Integer(this.weekNumber), mainFolder + "weekNumber.dat");


    
    }
    
    
    private void clearTable(JTable table)
    {
        System.out.print(table.getColumnCount());
        for (int i = 0; i < table.getRowCount(); i++) {
            for (int j = 0; j < table.getColumnCount(); j++) 
            {
                table.setValueAt("", i, j);
            }
        }
        
    }
    private void setTableRender(int columnCount, JTable table)
    {
                    DefaultTableCellRenderer center = new DefaultTableCellHeaderRenderer();
            center.setHorizontalAlignment(JLabel.CENTER);
            
            for (int i = 0; i < columnCount; i++)
                table.getColumnModel().getColumn(i).setCellRenderer(center);
    }
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        showPlayerFrame = new javax.swing.JFrame();
        showPlayersComboBox = new javax.swing.JComboBox();
        showPlayerframeButton = new javax.swing.JButton();
        addPlayerFrame = new javax.swing.JFrame();
        label1 = new java.awt.Label();
        label2 = new java.awt.Label();
        label4 = new java.awt.Label();
        label5 = new java.awt.Label();
        addPlayerIDField = new java.awt.TextField();
        addPlayerNameField = new java.awt.TextField();
        addPlayeBDField = new java.awt.TextField();
        addPlayerAdressField = new java.awt.TextField();
        addPlayerOKBUtton = new javax.swing.JButton();
        jButton2 = new javax.swing.JButton();
        editTeamFrame = new javax.swing.JFrame();
        editTeamFrameButton = new javax.swing.JButton();
        editTeamComboBox = new javax.swing.JComboBox();
        editTeamScreen = new javax.swing.JFrame();
        textField2 = new java.awt.TextField();
        textField3 = new java.awt.TextField();
        textField4 = new java.awt.TextField();
        textField5 = new java.awt.TextField();
        editTeamOKButton = new java.awt.Button();
        systemSpeqsFrame = new javax.swing.JFrame();
        jScrollPane1 = new javax.swing.JScrollPane();
        systemSpeqsTextArea = new javax.swing.JTextArea();
        topScorersFrame = new javax.swing.JFrame();
        jScrollPane2 = new javax.swing.JScrollPane();
        topScorersTable = new javax.swing.JTable();
        jLabel2 = new javax.swing.JLabel();
        topScorersOKButton = new javax.swing.JButton();
        editTeamButton = new javax.swing.JButton();
        showScheduleButton = new javax.swing.JButton();
        scheduleWeekComboBx = new javax.swing.JComboBox();
        showplayersButton = new javax.swing.JButton();
        scoreTableLabel = new javax.swing.JLabel();
        standingTablePane = new javax.swing.JScrollPane();
        standingTable = new javax.swing.JTable();
        scoreTablePane = new javax.swing.JScrollPane();
        scoreTable = new javax.swing.JTable();
        standingTableLabel = new java.awt.Label();
        playerTablePane = new javax.swing.JScrollPane();
        playerTable = new javax.swing.JTable();
        removePlayerButton = new javax.swing.JButton();
        addPlayerButton = new javax.swing.JButton();
        weeklyScoreShowComboBox = new javax.swing.JComboBox();
        showWeeklyScoreButton = new javax.swing.JButton();
        showSystemSpeqsButton = new javax.swing.JButton();
        showStandingTableButton = new javax.swing.JButton();
        showStandingTableComboBox = new javax.swing.JComboBox();
        playOneWeekButton = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        pictureBox = new javax.swing.JLabel();
        changeLeagueButton = new javax.swing.JButton();
        topScorersButton = new javax.swing.JButton();

        showPlayerFrame.setAlwaysOnTop(true);
        showPlayerFrame.setBounds(new java.awt.Rectangle(500, 500, 0, 0));
        showPlayerFrame.setMinimumSize(new java.awt.Dimension(500, 100));

        showPlayersComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                showPlayersComboBoxActionPerformed(evt);
            }
        });

        showPlayerframeButton.setText("Show");
        showPlayerframeButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                showPlayerframeButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout showPlayerFrameLayout = new javax.swing.GroupLayout(showPlayerFrame.getContentPane());
        showPlayerFrame.getContentPane().setLayout(showPlayerFrameLayout);
        showPlayerFrameLayout.setHorizontalGroup(
            showPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(showPlayerFrameLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(showPlayersComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, 188, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(showPlayerframeButton, javax.swing.GroupLayout.DEFAULT_SIZE, 87, Short.MAX_VALUE)
                .addContainerGap())
        );
        showPlayerFrameLayout.setVerticalGroup(
            showPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(showPlayerFrameLayout.createSequentialGroup()
                .addGap(29, 29, 29)
                .addGroup(showPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(showPlayersComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(showPlayerframeButton, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(27, Short.MAX_VALUE))
        );

        addPlayerFrame.setMinimumSize(new java.awt.Dimension(408, 250));

        label1.setText("Name");

        label2.setText("ID");

        label4.setText("Adress");

        label5.setText("Birth Date");

        addPlayerIDField.setText("Enter ID");
        addPlayerIDField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addPlayerIDFieldActionPerformed(evt);
            }
        });

        addPlayerNameField.setText("Enter Name");

        addPlayeBDField.setText("Enter B.D.");

        addPlayerAdressField.setText("Enter Adress");

        addPlayerOKBUtton.setText("OK");
        addPlayerOKBUtton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addPlayerOKBUttonActionPerformed(evt);
            }
        });

        jButton2.setText("Cancel");
        jButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton2ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout addPlayerFrameLayout = new javax.swing.GroupLayout(addPlayerFrame.getContentPane());
        addPlayerFrame.getContentPane().setLayout(addPlayerFrameLayout);
        addPlayerFrameLayout.setHorizontalGroup(
            addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, addPlayerFrameLayout.createSequentialGroup()
                .addContainerGap(20, Short.MAX_VALUE)
                .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(addPlayerFrameLayout.createSequentialGroup()
                        .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(40, 40, 40)
                        .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(addPlayerIDField, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(addPlayerNameField, javax.swing.GroupLayout.DEFAULT_SIZE, 250, Short.MAX_VALUE)))
                    .addGroup(addPlayerFrameLayout.createSequentialGroup()
                        .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(label5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(20, 20, 20)
                        .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(addPlayeBDField, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(addPlayerAdressField, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, addPlayerFrameLayout.createSequentialGroup()
                                .addComponent(addPlayerOKBUtton, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 82, Short.MAX_VALUE)
                                .addComponent(jButton2, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(8, 8, 8)))))
                .addGap(60, 60, 60))
        );
        addPlayerFrameLayout.setVerticalGroup(
            addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(addPlayerFrameLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(addPlayerIDField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(label1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(addPlayerNameField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(label5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(addPlayeBDField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(label4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(addPlayerAdressField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(26, 26, 26)
                .addGroup(addPlayerFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(addPlayerOKBUtton)
                    .addComponent(jButton2))
                .addContainerGap(22, Short.MAX_VALUE))
        );

        editTeamFrame.setMinimumSize(new java.awt.Dimension(400, 150));

        editTeamFrameButton.setText("Edit");
        editTeamFrameButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                editTeamFrameButtonActionPerformed(evt);
            }
        });

        editTeamComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                editTeamComboBoxActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout editTeamFrameLayout = new javax.swing.GroupLayout(editTeamFrame.getContentPane());
        editTeamFrame.getContentPane().setLayout(editTeamFrameLayout);
        editTeamFrameLayout.setHorizontalGroup(
            editTeamFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(editTeamFrameLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(editTeamComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, 188, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(editTeamFrameButton, javax.swing.GroupLayout.DEFAULT_SIZE, 174, Short.MAX_VALUE)
                .addContainerGap())
        );
        editTeamFrameLayout.setVerticalGroup(
            editTeamFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(editTeamFrameLayout.createSequentialGroup()
                .addGap(29, 29, 29)
                .addGroup(editTeamFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(editTeamComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(editTeamFrameButton, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(51, Short.MAX_VALUE))
        );

        editTeamScreen.setMinimumSize(new java.awt.Dimension(400, 400));

        textField2.setText("textField2");

        textField3.setText("textField3");

        textField4.setText("textField4");

        textField5.setText("textField5");

        editTeamOKButton.setLabel("OK");
        editTeamOKButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                editTeamOKButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout editTeamScreenLayout = new javax.swing.GroupLayout(editTeamScreen.getContentPane());
        editTeamScreen.getContentPane().setLayout(editTeamScreenLayout);
        editTeamScreenLayout.setHorizontalGroup(
            editTeamScreenLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, editTeamScreenLayout.createSequentialGroup()
                .addContainerGap(47, Short.MAX_VALUE)
                .addGroup(editTeamScreenLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(textField5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(textField4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(textField3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(textField2, javax.swing.GroupLayout.PREFERRED_SIZE, 310, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(editTeamScreenLayout.createSequentialGroup()
                        .addGap(112, 112, 112)
                        .addComponent(editTeamOKButton, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addGap(43, 43, 43))
        );

        editTeamScreenLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {textField2, textField3, textField4, textField5});

        editTeamScreenLayout.setVerticalGroup(
            editTeamScreenLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(editTeamScreenLayout.createSequentialGroup()
                .addGap(24, 24, 24)
                .addComponent(textField2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(28, 28, 28)
                .addComponent(textField3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(30, 30, 30)
                .addComponent(textField4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(20, 20, 20)
                .addComponent(textField5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(20, 20, 20)
                .addComponent(editTeamOKButton, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(23, Short.MAX_VALUE))
        );

        systemSpeqsFrame.setMinimumSize(new java.awt.Dimension(400, 300));

        systemSpeqsTextArea.setEditable(false);
        systemSpeqsTextArea.setColumns(20);
        systemSpeqsTextArea.setRows(5);
        jScrollPane1.setViewportView(systemSpeqsTextArea);

        javax.swing.GroupLayout systemSpeqsFrameLayout = new javax.swing.GroupLayout(systemSpeqsFrame.getContentPane());
        systemSpeqsFrame.getContentPane().setLayout(systemSpeqsFrameLayout);
        systemSpeqsFrameLayout.setHorizontalGroup(
            systemSpeqsFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(systemSpeqsFrameLayout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 250, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(122, Short.MAX_VALUE))
        );
        systemSpeqsFrameLayout.setVerticalGroup(
            systemSpeqsFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(systemSpeqsFrameLayout.createSequentialGroup()
                .addGap(21, 21, 21)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 268, Short.MAX_VALUE)
                .addContainerGap())
        );

        topScorersFrame.setMinimumSize(new java.awt.Dimension(372, 500));

        topScorersTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null}
            },
            new String [] {
                "Name", "Team", "Goals"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.String.class, java.lang.Integer.class
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }
        });
        jScrollPane2.setViewportView(topScorersTable);
        if (topScorersTable.getColumnModel().getColumnCount() > 0) {
            topScorersTable.getColumnModel().getColumn(2).setPreferredWidth(15);
        }

        jLabel2.setText("TOP SCORERES");

        topScorersOKButton.setText("OK");
        topScorersOKButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                topScorersOKButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout topScorersFrameLayout = new javax.swing.GroupLayout(topScorersFrame.getContentPane());
        topScorersFrame.getContentPane().setLayout(topScorersFrameLayout);
        topScorersFrameLayout.setHorizontalGroup(
            topScorersFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, topScorersFrameLayout.createSequentialGroup()
                .addContainerGap(24, Short.MAX_VALUE)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 328, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(20, 20, 20))
            .addGroup(topScorersFrameLayout.createSequentialGroup()
                .addGroup(topScorersFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(topScorersFrameLayout.createSequentialGroup()
                        .addGap(142, 142, 142)
                        .addComponent(jLabel2))
                    .addGroup(topScorersFrameLayout.createSequentialGroup()
                        .addGap(151, 151, 151)
                        .addComponent(topScorersOKButton, javax.swing.GroupLayout.PREFERRED_SIZE, 55, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        topScorersFrameLayout.setVerticalGroup(
            topScorersFrameLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(topScorersFrameLayout.createSequentialGroup()
                .addGap(17, 17, 17)
                .addComponent(jLabel2)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 347, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(topScorersOKButton, javax.swing.GroupLayout.DEFAULT_SIZE, 32, Short.MAX_VALUE)
                .addContainerGap())
        );

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("TFFL");
        setBackground(new java.awt.Color(204, 204, 204));
        setName("masterFrame"); // NOI18N

        editTeamButton.setText("Edit Team");
        editTeamButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                editTeamButtonActionPerformed(evt);
            }
        });

        showScheduleButton.setText("  Show \nSchedule");
        showScheduleButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                showScheduleButtonActionPerformed(evt);
            }
        });

        scheduleWeekComboBx.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34" }));
        scheduleWeekComboBx.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                scheduleWeekComboBxActionPerformed(evt);
            }
        });

        showplayersButton.setText("Show Players");
        showplayersButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                showplayersButtonActionPerformed(evt);
            }
        });

        scoreTableLabel.setText("Score/Schedule Table");

        standingTable.setBackground(new java.awt.Color(255, 204, 204));
        standingTable.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        standingTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null},
                {null, null, null, null, null, null, null, null, null, null}
            },
            new String [] {
                "Order", "Team Name", "Week", "Score", "Win", "Lose", "Draw", "Goals For", "Goals Against", "Average"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.Integer.class, java.lang.String.class, java.lang.Integer.class, java.lang.Integer.class, java.lang.Integer.class, java.lang.Integer.class, java.lang.Integer.class, java.lang.Integer.class, java.lang.Integer.class, java.lang.Integer.class
            };
            boolean[] canEdit = new boolean [] {
                false, false, false, false, false, false, false, false, false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        standingTable.setToolTipText("");
        standingTable.setGridColor(new java.awt.Color(51, 0, 51));
        standingTable.setOpaque(false);
        standingTable.setSelectionBackground(new java.awt.Color(51, 102, 255));
        standingTable.setSelectionForeground(new java.awt.Color(0, 0, 0));
        standingTablePane.setViewportView(standingTable);
        if (standingTable.getColumnModel().getColumnCount() > 0) {
            standingTable.getColumnModel().getColumn(0).setResizable(false);
            standingTable.getColumnModel().getColumn(0).setPreferredWidth(5);
            standingTable.getColumnModel().getColumn(1).setResizable(false);
            standingTable.getColumnModel().getColumn(1).setPreferredWidth(120);
            standingTable.getColumnModel().getColumn(2).setResizable(false);
            standingTable.getColumnModel().getColumn(2).setPreferredWidth(15);
            standingTable.getColumnModel().getColumn(3).setResizable(false);
            standingTable.getColumnModel().getColumn(3).setPreferredWidth(15);
            standingTable.getColumnModel().getColumn(4).setResizable(false);
            standingTable.getColumnModel().getColumn(4).setPreferredWidth(15);
            standingTable.getColumnModel().getColumn(5).setResizable(false);
            standingTable.getColumnModel().getColumn(5).setPreferredWidth(15);
            standingTable.getColumnModel().getColumn(6).setResizable(false);
            standingTable.getColumnModel().getColumn(6).setPreferredWidth(15);
            standingTable.getColumnModel().getColumn(7).setResizable(false);
            standingTable.getColumnModel().getColumn(7).setPreferredWidth(15);
            standingTable.getColumnModel().getColumn(8).setResizable(false);
            standingTable.getColumnModel().getColumn(8).setPreferredWidth(15);
            standingTable.getColumnModel().getColumn(9).setResizable(false);
            standingTable.getColumnModel().getColumn(9).setPreferredWidth(15);
        }

        scoreTable.setBackground(new java.awt.Color(255, 204, 204));
        scoreTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null, null},
                {null, null, null, null, null},
                {null, null, null, null, null},
                {null, null, null, null, null},
                {null, null, null, null, null},
                {null, null, null, null, null},
                {null, null, null, null, null},
                {null, null, null, null, null},
                {null, null, null, null, null}
            },
            new String [] {
                "Team Name   Score     Score Team Name", "Score", "Score", "Team Name", "Time"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.Integer.class, java.lang.Integer.class, java.lang.String.class, java.lang.String.class
            };
            boolean[] canEdit = new boolean [] {
                false, false, false, false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        scoreTable.setSelectionForeground(new java.awt.Color(0, 0, 0));
        scoreTablePane.setViewportView(scoreTable);
        if (scoreTable.getColumnModel().getColumnCount() > 0) {
            scoreTable.getColumnModel().getColumn(0).setResizable(false);
            scoreTable.getColumnModel().getColumn(0).setPreferredWidth(80);
            scoreTable.getColumnModel().getColumn(1).setResizable(false);
            scoreTable.getColumnModel().getColumn(2).setResizable(false);
            scoreTable.getColumnModel().getColumn(3).setResizable(false);
            scoreTable.getColumnModel().getColumn(4).setResizable(false);
            scoreTable.getColumnModel().getColumn(4).setPreferredWidth(40);
        }

        standingTableLabel.setText("Standing Table");

        playerTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "ID", "Name", "Age", "Team"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.String.class, java.lang.Integer.class, java.lang.String.class
            };
            boolean[] canEdit = new boolean [] {
                false, false, false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        playerTablePane.setViewportView(playerTable);
        if (playerTable.getColumnModel().getColumnCount() > 0) {
            playerTable.getColumnModel().getColumn(0).setResizable(false);
            playerTable.getColumnModel().getColumn(0).setPreferredWidth(30);
            playerTable.getColumnModel().getColumn(1).setResizable(false);
            playerTable.getColumnModel().getColumn(1).setPreferredWidth(60);
            playerTable.getColumnModel().getColumn(2).setPreferredWidth(3);
            playerTable.getColumnModel().getColumn(3).setResizable(false);
            playerTable.getColumnModel().getColumn(3).setPreferredWidth(5);
        }

        removePlayerButton.setText("Remove Player");
        removePlayerButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                removePlayerButtonActionPerformed(evt);
            }
        });

        addPlayerButton.setText("Add Player");
        addPlayerButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addPlayerButtonActionPerformed(evt);
            }
        });

        weeklyScoreShowComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34" }));
        weeklyScoreShowComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                weeklyScoreShowComboBoxActionPerformed(evt);
            }
        });

        showWeeklyScoreButton.setText("Show Weekly Score");
        showWeeklyScoreButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                showWeeklyScoreButtonActionPerformed(evt);
            }
        });

        showSystemSpeqsButton.setText("Show System Speqs");
        showSystemSpeqsButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                showSystemSpeqsButtonActionPerformed(evt);
            }
        });

        showStandingTableButton.setText("Show Standing Table");
        showStandingTableButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                showStandingTableButtonActionPerformed(evt);
            }
        });

        showStandingTableComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34" }));

        playOneWeekButton.setText("Play One Week");
        playOneWeekButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                playOneWeekButtonActionPerformed(evt);
            }
        });

        jLabel1.setText("Player List");

        pictureBox.setPreferredSize(new java.awt.Dimension(502, 115));

        changeLeagueButton.setText("Change League");
        changeLeagueButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                changeLeagueButtonActionPerformed(evt);
            }
        });

        topScorersButton.setText("Top Scorers");
        topScorersButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                topScorersButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(20, 20, 20)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                            .addComponent(weeklyScoreShowComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(scheduleWeekComboBx, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addComponent(showScheduleButton, javax.swing.GroupLayout.PREFERRED_SIZE, 126, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(showWeeklyScoreButton, javax.swing.GroupLayout.PREFERRED_SIZE, 126, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                    .addComponent(scoreTableLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 184, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(170, 170, 170)
                                .addComponent(jLabel1))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(scoreTablePane, javax.swing.GroupLayout.PREFERRED_SIZE, 343, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(showplayersButton, javax.swing.GroupLayout.PREFERRED_SIZE, 123, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(editTeamButton, javax.swing.GroupLayout.DEFAULT_SIZE, 96, Short.MAX_VALUE)
                                        .addGap(29, 29, 29)
                                        .addComponent(addPlayerButton, javax.swing.GroupLayout.PREFERRED_SIZE, 123, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(18, 18, 18)
                                        .addComponent(removePlayerButton, javax.swing.GroupLayout.PREFERRED_SIZE, 123, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addComponent(playerTablePane, javax.swing.GroupLayout.PREFERRED_SIZE, 571, javax.swing.GroupLayout.PREFERRED_SIZE))))
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(showSystemSpeqsButton)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(changeLeagueButton))
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(standingTableLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(standingTablePane, javax.swing.GroupLayout.PREFERRED_SIZE, 923, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                    .addComponent(playOneWeekButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(showStandingTableComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(18, 18, 18)
                                        .addComponent(showStandingTableButton))
                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(topScorersButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))))
                        .addGap(0, 0, Short.MAX_VALUE))))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(pictureBox, javax.swing.GroupLayout.PREFERRED_SIZE, 1012, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(60, 60, 60))
        );

        layout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {editTeamButton, showplayersButton});

        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addComponent(pictureBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(standingTableLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(standingTablePane, javax.swing.GroupLayout.PREFERRED_SIZE, 316, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(playOneWeekButton, javax.swing.GroupLayout.PREFERRED_SIZE, 37, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(50, 50, 50)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                            .addComponent(showStandingTableComboBox, javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(showStandingTableButton, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.PREFERRED_SIZE, 38, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(139, 139, 139)
                        .addComponent(topScorersButton, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(scoreTableLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 26, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel1))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(scoreTablePane, javax.swing.GroupLayout.PREFERRED_SIZE, 175, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(showScheduleButton, javax.swing.GroupLayout.PREFERRED_SIZE, 33, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(scheduleWeekComboBx, javax.swing.GroupLayout.PREFERRED_SIZE, 33, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addComponent(playerTablePane, javax.swing.GroupLayout.PREFERRED_SIZE, 203, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(weeklyScoreShowComboBox)
                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(showWeeklyScoreButton, javax.swing.GroupLayout.PREFERRED_SIZE, 33, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(showplayersButton, javax.swing.GroupLayout.PREFERRED_SIZE, 38, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(removePlayerButton, javax.swing.GroupLayout.PREFERRED_SIZE, 38, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(addPlayerButton, javax.swing.GroupLayout.PREFERRED_SIZE, 38, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(editTeamButton, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addGap(53, 53, 53)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(changeLeagueButton, javax.swing.GroupLayout.PREFERRED_SIZE, 37, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(showSystemSpeqsButton, javax.swing.GroupLayout.PREFERRED_SIZE, 48, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(0, 0, 0))
        );

        layout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {changeLeagueButton, showSystemSpeqsButton});

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void showScheduleButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_showScheduleButtonActionPerformed

        int week;
        
        week = scheduleWeekComboBx.getSelectedIndex();
        System.out.println(week);
        try {
            ScheduleTable table = (ScheduleTable) FileOperations.readBinary(mainFolder + "Schedules/scheduleWeek" + (week+1) + ".dat"); //check
            String [] str = table.printTable();
            
            for (int i = 0; i < str.length; i++) {
                this.scoreTable.setValueAt(table.get(i).getTeam1(), i, 0);
                this.scoreTable.setValueAt("?", i, 1);
                this.scoreTable.setValueAt("?", i, 2);
                this.scoreTable.setValueAt(table.get(i).getTeam2(), i, 3);
                this.scoreTable.setValueAt(table.get(i).getTime(), i, 4);
            }
            
            this.setTableRender(this.scoreTable.getColumnCount(), this.scoreTable);
            
            
        } catch (IOException | ClassNotFoundException | CloneNotSupportedException ex) {
            Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
        }


    }//GEN-LAST:event_showScheduleButtonActionPerformed

    private void scheduleWeekComboBxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_scheduleWeekComboBxActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_scheduleWeekComboBxActionPerformed

    private void showplayersButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_showplayersButtonActionPerformed

        this.clearTable(this.playerTable);
        showPlayerFrame.setVisible(true);
        
        File folder = new File(mainFolder + "Teams");
        File [] files = folder.listFiles();
        DefaultComboBoxModel model = (DefaultComboBoxModel) showPlayersComboBox.getModel();
        
        for (File file : files) 
            if (model.getIndexOf(file.getName()) == -1) 
            {
                int pos = file.getName().lastIndexOf(".");
                String name = file.getName().substring(0,pos);
                showPlayersComboBox.addItem(name);
            }
   
        showPlayerframeButton.addActionListener((ActionEvent e) -> {
            String teamName = (String)showPlayersComboBox.getSelectedItem();    
            try
            {
                Team team = (Team) FileOperations.readBinary(mainFolder + "Teams/" + teamName + ".dat");
                String [] players = team.getPlayers();
                Player player;
                
                for (int i = 0; i < team.size() ; i++) 
                {
                    player = (Player) FileOperations.readBinary(mainFolder + "Players/" + players[i] + ".dat");

                    playerTable.setValueAt(player.getID(), i, 0);
                    playerTable.setValueAt(player.getName(), i, 1);
                    playerTable.setValueAt(player.getTeam(), i, 3);
                    playerTable.setValueAt(player.getBirthDate(), i, 2);
                    
                }
                showPlayerFrame.dispose();
            } catch (IOException | ClassNotFoundException ex) {
                Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
    }//GEN-LAST:event_showplayersButtonActionPerformed

    private void showPlayerframeButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_showPlayerframeButtonActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_showPlayerframeButtonActionPerformed

    private void removePlayerButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_removePlayerButtonActionPerformed
       
        int row = playerTable.getSelectedRow();
        if(row == -1)
            return;
        String playerID = (String)playerTable.getValueAt(row, 0);

        if(playerID == null)
            return;
        try 
        {
            Player player = (Player) FileOperations.readBinary(mainFolder + "Players/" + playerID + ".dat");
            File file = new File(mainFolder + "Players/" + playerID + ".dat");
            if(file.isFile())
                file.delete();
            else
                return;
            Team team = (Team)FileOperations.readBinary(mainFolder + "Teams/" + player.getTeam() + ".dat");
            team.removePlayer(player.getID());
            FileOperations.writeBinary(team ,mainFolder + "Teams/" + team.getName() + ".dat");
            
            this.playerTable.setValueAt("", row, 0);
            this.playerTable.setValueAt("", row, 1);
            this.playerTable.setValueAt("", row, 2);
            this.playerTable.setValueAt("", row, 3);
             
            
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        
        
    }//GEN-LAST:event_removePlayerButtonActionPerformed

    private void addPlayerIDFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_addPlayerIDFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_addPlayerIDFieldActionPerformed

    private void addPlayerOKBUttonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_addPlayerOKBUttonActionPerformed
        
        
        if(!this.addPlayerIDField.getText().equals("Enter ID") && !this.addPlayerIDField.getText().equals("") &&
           !this.addPlayerNameField.getText().equals("Enter ID") && !this.addPlayerNameField.getText().equals("Enter ID") &&
           !this.addPlayeBDField.getText().equals("Enter ID")  && !this.addPlayeBDField.getText().equals("Enter ID") &&
           !this.addPlayerAdressField.getText().equals("Enter ID") && !this.addPlayerAdressField.getText().equals("Enter ID"))
        {
        
            File file = new File(mainFolder + "Players/" + this.addPlayerIDField + ".dat");
            if(file.isFile()){
                JOptionPane.showMessageDialog(this, "The ID is exist !!");
                addPlayerFrame.dispose();            
            }
            Player player = new Player();
            player.setID(this.addPlayerIDField.getText());
            player.setName(this.addPlayerNameField.getText());
            player.setBirthDate(this.addPlayeBDField.getText());
            player.setTeam((String)showPlayersComboBox.getSelectedItem());
            player.setAdress(this.addPlayerAdressField.getText());

            try {
                Team   team = (Team) FileOperations.readBinary(mainFolder + "Teams/" + showPlayersComboBox.getSelectedItem() + ".dat");
                FileOperations.writeBinary(player, mainFolder + "Players/" + player.getID() + ".dat");
                team.addPlayer(player.getID());
                FileOperations.writeBinary(team, mainFolder + "Teams/" + showPlayersComboBox.getSelectedItem() + ".dat");
            } catch (IOException | ClassNotFoundException ex) {
                Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
            }

            DefaultTableModel model =  (DefaultTableModel)this.playerTable.getModel();
            addPlayerFrame.dispose();
        }else
        {
            addPlayerFrame.dispose();
            JOptionPane.showMessageDialog(this, "Missing infos, it will not be saved");
        }

    }//GEN-LAST:event_addPlayerOKBUttonActionPerformed

    private void jButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton2ActionPerformed

        this.addPlayerFrame.dispose();
    }//GEN-LAST:event_jButton2ActionPerformed

    private void addPlayerButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_addPlayerButtonActionPerformed

        if(this.playerTable.getValueAt(0, 0) == null)
            JOptionPane.showMessageDialog(this, "Before select team");
        else
        {
            this.addPlayerFrame.setVisible(true);
        
            Team team = null; 
            try {
                team = (Team) FileOperations.readBinary(mainFolder + "Teams/" + showPlayersComboBox.getSelectedItem() + ".dat");
            } catch (IOException | ClassNotFoundException ex) {
                Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
            }
                if(team.size() == 11){
                     JOptionPane.showMessageDialog(this, "Team is Full");
                     this.addPlayerFrame.dispose();
                 }
        }
    }//GEN-LAST:event_addPlayerButtonActionPerformed

    private void editTeamFrameButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_editTeamFrameButtonActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_editTeamFrameButtonActionPerformed

    private void showPlayersComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_showPlayersComboBoxActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_showPlayersComboBoxActionPerformed

    private void editTeamButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_editTeamButtonActionPerformed
        editTeamFrame.setVisible(true);
        
        File folder = new File(mainFolder + "Teams");
        File [] files = folder.listFiles();
        DefaultComboBoxModel model = (DefaultComboBoxModel) showPlayersComboBox.getModel();

        for (File file : files) 
            if (model.getIndexOf(file.getName()) == -1) 
                editTeamComboBox.addItem(file.getName());

        this.editTeamFrameButton.addActionListener((ActionEvent e) ->
        {
            String teamName = (String) editTeamComboBox.getSelectedItem();
            try
            {
                Team team = (Team) FileOperations.readBinary(mainFolder + "Teams/" + teamName);
                textField2.setText(Integer.toString(team.getYear()));
                textField3.setText(team.getPresident());
                textField4.setText(team.getVicePresidentId());
                textField5.setText(team.getCoachID());
                editTeamScreen.setVisible(true);

                
                
            } catch (IOException | ClassNotFoundException | CloneNotSupportedException ex) {
                Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
    }//GEN-LAST:event_editTeamButtonActionPerformed

    private void editTeamComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_editTeamComboBoxActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_editTeamComboBoxActionPerformed

    private void editTeamOKButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_editTeamOKButtonActionPerformed
                       

        String teamName = (String) editTeamComboBox.getSelectedItem();
        Team team;
        try {
            team = (Team) FileOperations.readBinary(mainFolder + "Teams/" + teamName);
            team.setYear(Integer.parseInt(textField2.getText()));
            team.setPresident(textField3.getText());
            team.setVicePresident(textField4.getText());
            team.setCoachID(textField5.getText());
            
            Files.delete(Paths.get(mainFolder + "Teams/" + teamName));
            FileOperations.writeBinary(team, (mainFolder + "Teams/" + team.getName() + ".dat"));
            editTeamFrame.dispose();
            editTeamScreen.dispose();
            this.fillStandingTable(this.weekNumber);
        } catch (IOException | ClassNotFoundException | CloneNotSupportedException ex) {
            Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
        }

                
                
    }//GEN-LAST:event_editTeamOKButtonActionPerformed

    private void weeklyScoreShowComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_weeklyScoreShowComboBoxActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_weeklyScoreShowComboBoxActionPerformed

    private void showWeeklyScoreButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_showWeeklyScoreButtonActionPerformed
        
        int week = Integer.parseInt((String)weeklyScoreShowComboBox.getSelectedItem());
        
        File file = new File (mainFolder + "Scores/score" + week + ".dat");
        if(!file.isFile())
            JOptionPane.showMessageDialog(this, "The scores were not been entered");
        else
        {
            try 
            {
                ScoreTable currentScores = (ScoreTable) FileOperations.readBinary(mainFolder + "Scores/score" + week + ".dat");
                for (int i = 0; i < currentScores.size(); i++)
                {
                    this.scoreTable.setValueAt(currentScores.get(i).getTeam1(), i, 0);
                    this.scoreTable.setValueAt(currentScores.get(i).getScore1(), i, 1);
                    this.scoreTable.setValueAt(currentScores.get(i).getScore2(), i, 2);
                    this.scoreTable.setValueAt(currentScores.get(i).getTeam2(), i, 3);
                    this.scoreTable.setValueAt(currentScores.get(i).getTime(), i, 4);
                    

               }
                
                
            } catch (IOException | ClassNotFoundException | CloneNotSupportedException ex) {
                Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
            }
                     
            this.setTableRender(this.scoreTable.getColumnCount(), this.scoreTable);

        
        }
        
        
    }//GEN-LAST:event_showWeeklyScoreButtonActionPerformed

    private void showSystemSpeqsButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_showSystemSpeqsButtonActionPerformed
    
        File  folder = new File(mainFolder + "TFFL Managers");
        File [] files = folder.listFiles();
        TFFLManager manager;
        
        for (int i = 0; i < files.length; i++) {
            try {
                manager = (TFFLManager) FileOperations.readBinary(mainFolder + "TFFL Managers/" + files[i].getName());
                if(manager.getType().equals("pre"))
                    this.president = manager;
                else
                    this.vicePresident = manager;
            } catch (IOException | ClassNotFoundException ex) {
                Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
            }          
        }
        systemSpeqsTextArea.setText("TURKEY FOOTBALL FEDEATION LEAGUE\n" + "PRESIDENT\n" + this.president.toString() + "\nVICE PRESIDENT" + this.vicePresident.toString());
        systemSpeqsFrame.setVisible(true);
        
    }//GEN-LAST:event_showSystemSpeqsButtonActionPerformed

    private void showStandingTableButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_showStandingTableButtonActionPerformed

        File file = new File(mainFolder + "Standing Tables/table" + showStandingTableComboBox.getSelectedItem() + ".dat");
        
        if(!file.isFile())
            JOptionPane.showMessageDialog(this, "Not even played matches for this week");
        else
            try {
                fillStandingTable(Integer.parseInt(showStandingTableComboBox.getSelectedItem().toString()));
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
        }
            
        

    }//GEN-LAST:event_showStandingTableButtonActionPerformed

    private void playOneWeekButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_playOneWeekButtonActionPerformed
        try {
            if(this.weekNumber != 34)
                this.playOneWeek();
            else
                JOptionPane.showMessageDialog(this, "The year has finished, i think yo do not want play more");
        } catch (IOException | ClassNotFoundException | CloneNotSupportedException ex) {
            Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_playOneWeekButtonActionPerformed

    private void changeLeagueButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_changeLeagueButtonActionPerformed
       
        
        
        do{
        if (chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION)
            mainFolder = chooser.getSelectedFile().toString() + "/";
        else
        {
            JOptionPane.showMessageDialog(this,"any file was did not selected");
            return;
        }

        if(!new File(mainFolder + "Teams").isDirectory() && !new File(mainFolder + "Teams.csv").exists())
            JOptionPane.showMessageDialog(this, "Missing files, returning");
        }while(!new File(mainFolder + "Teams").isDirectory() && !new File(mainFolder + "Teams.csv").exists());   
        
        try
        {
            if(new File(mainFolder + "weekNumber.dat").exists())
                this.weekNumber = (Integer) FileOperations.readBinary(mainFolder + "weekNumber.dat");
            else
                this.weekNumber = 0;
                
            if(!Files.isDirectory(Paths.get(mainFolder + "Teams")))
            {           
                this.readTeams(mainFolder + "Teams");
                this.readTFFLManagers();
                this.readTeamManagers();
                this.readPlayers();
                this.verifyDatas();
                this.matchDatas();
                this.autoSchedule();
                this.createStandings();
                
                this.scoreTable.removeAll();
            }
            this.pictureBox.setIcon(new javax.swing.ImageIcon("logo.jpg"));
            

            this.setupTables();
            this.fillStandingTable(this.weekNumber);
            this.clearTable(scoreTable);
            this.clearTable(playerTable);
        } catch (CloneNotSupportedException | ClassNotFoundException | BadAlloc | TFFLFileNotExistException | IOException ex) {
                Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
        }

        
    }//GEN-LAST:event_changeLeagueButtonActionPerformed

    private void topScorersButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_topScorersButtonActionPerformed

        if(this.weekNumber == 0)
        {
            JOptionPane.showMessageDialog(this, "No match score");
            return;
        }
        try 
        {
            this.topScorer();
            this.topScorersFrame.setVisible(true);
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_topScorersButtonActionPerformed

    private void topScorersOKButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_topScorersOKButtonActionPerformed

        this.topScorersFrame.dispose();
    }//GEN-LAST:event_topScorersOKButtonActionPerformed

    /**
     * @param args the command line arguments
     * @throws java.lang.CloneNotSupportedException
     * @throws java.io.IOException
     */
    public static void main(String args[]) throws CloneNotSupportedException, IndexOutOfBoundsException, IOException
    {
     
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(TFFLGui.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        
        //</editor-fold>

      
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
            
                try {
                    TFFLGui gui = new TFFLGui();
                    gui.setResizable(false);
                    gui.setVisible(true);
                } catch (IOException | CloneNotSupportedException | ClassNotFoundException | TFFLFileNotExistException | BadAlloc | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException ex) {
                    Logger.getLogger(TFFLGui.class.getName()).log(Level.SEVERE, null, ex);
                }
                
            }
        });
    }

    

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private java.awt.TextField addPlayeBDField;
    private java.awt.TextField addPlayerAdressField;
    private javax.swing.JButton addPlayerButton;
    private javax.swing.JFrame addPlayerFrame;
    private java.awt.TextField addPlayerIDField;
    private java.awt.TextField addPlayerNameField;
    private javax.swing.JButton addPlayerOKBUtton;
    private javax.swing.JButton changeLeagueButton;
    private javax.swing.JButton editTeamButton;
    private javax.swing.JComboBox editTeamComboBox;
    private javax.swing.JFrame editTeamFrame;
    private javax.swing.JButton editTeamFrameButton;
    private java.awt.Button editTeamOKButton;
    private javax.swing.JFrame editTeamScreen;
    private javax.swing.JButton jButton2;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private java.awt.Label label1;
    private java.awt.Label label2;
    private java.awt.Label label4;
    private java.awt.Label label5;
    private javax.swing.JLabel pictureBox;
    private javax.swing.JButton playOneWeekButton;
    private javax.swing.JTable playerTable;
    private javax.swing.JScrollPane playerTablePane;
    private javax.swing.JButton removePlayerButton;
    private javax.swing.JComboBox scheduleWeekComboBx;
    private javax.swing.JTable scoreTable;
    private javax.swing.JLabel scoreTableLabel;
    private javax.swing.JScrollPane scoreTablePane;
    private javax.swing.JFrame showPlayerFrame;
    private javax.swing.JButton showPlayerframeButton;
    private javax.swing.JComboBox showPlayersComboBox;
    private javax.swing.JButton showScheduleButton;
    private javax.swing.JButton showStandingTableButton;
    private javax.swing.JComboBox showStandingTableComboBox;
    private javax.swing.JButton showSystemSpeqsButton;
    private javax.swing.JButton showWeeklyScoreButton;
    private javax.swing.JButton showplayersButton;
    private javax.swing.JTable standingTable;
    private java.awt.Label standingTableLabel;
    private javax.swing.JScrollPane standingTablePane;
    private javax.swing.JFrame systemSpeqsFrame;
    private javax.swing.JTextArea systemSpeqsTextArea;
    private java.awt.TextField textField2;
    private java.awt.TextField textField3;
    private java.awt.TextField textField4;
    private java.awt.TextField textField5;
    private javax.swing.JButton topScorersButton;
    private javax.swing.JFrame topScorersFrame;
    private javax.swing.JButton topScorersOKButton;
    private javax.swing.JTable topScorersTable;
    private javax.swing.JComboBox weeklyScoreShowComboBox;
    // End of variables declaration//GEN-END:variables
}
